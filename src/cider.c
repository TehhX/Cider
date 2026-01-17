#include "cider.h"

#include "stdlib.h"
#include "string.h"

#if CIDER_PLATFORM == CIDER_PLAT_WIN
    #include "libloaderapi.h" // For GetModuleFileNameA(...)

    #ifndef PATH_MAX
        #include "minwindef.h" // Contains MAX_PATH
        #define PATH_MAX MAX_PATH
    #endif

    #define home_env_str() getenv("APPDATA")
#elif CIDER_PLATFORM == CIDER_PLAT_LIN
    #include "linux/limits.h" // For PATH_MAX
    #include "unistd.h" // For readlink(...)

    #define home_env_str() getenv("HOME")
#endif

char *cider_data_filepath()
{
    char *data_filepath = home_env_str();
    const int data_filepath_len = strlen(data_filepath);

#if CIDER_PLATFORM == CIDER_PLAT_LIN
 #define LIN_LOCAL "/.local/share/"
    data_filepath = memcpy(malloc(data_filepath_len + sizeof(LIN_LOCAL)), data_filepath, data_filepath_len);
    memcpy(data_filepath + data_filepath_len, LIN_LOCAL, sizeof(LIN_LOCAL));
 #undef LIN_LOCAL
#elif CIDER_PLATFORM == CIDER_PLAT_WIN
    data_filepath = strcpy(malloc(data_filepath_len + 2), data_filepath);
    data_filepath[data_filepath_len] = CIDER_PATH_DELIM;
    data_filepath[data_filepath_len + 1] = 0;
#endif

    return data_filepath;
}

char *cider_exec_fullname()
{
    char * const fullpath = malloc(PATH_MAX + 1);

#if CIDER_PLATFORM == CIDER_PLAT_LIN
    const int fullpath_len = readlink("/proc/self/exe", fullpath, PATH_MAX) + 1;
#elif CIDER_PLATFORM == CIDER_PLAT_WIN
    const int fullpath_len = GetModuleFileNameA(0, fullpath, PATH_MAX) + 1;
#endif

    fullpath[fullpath_len - 1] = 0;
    return realloc(fullpath, fullpath_len);
}

char *cider_to_filepath(char *file)
{
    const int file_len = strlen(file);

    for (int i = file_len - 1; i >= 0; --i)
    {
        if (file[i] == CIDER_PATH_DELIM)
        {
            file[i + 1] = '\0';
            return realloc(file, i + 2);
        }
    }

    return NULL;
}

char *cider_to_filename(char *file)
{
    const int file_len = strlen(file);

    for (int i = file_len - 1; i >= 0; --i)
    {
        if (file[i] == CIDER_PATH_DELIM)
        {
            memmove(file, file + i + 1, file_len - i);
            return realloc(file, file_len - i);
        }
    }

    return NULL;
}

char *cider_to_extension(char *file)
{
    const int file_len = strlen(file);

    for (int i = file_len - 1; i >= 0; --i)
    {
        if (file[i] == '.')
        {
            memmove(file, file + i + 1, file_len - i);
            return realloc(file, file_len - i);
        }
    }

    return NULL;
}

char *cider_construct_fullname(const char *filepath, const char *filename)
{
    const int
        filepath_len = strlen(filepath),
        fullname_len = filepath_len + strlen(filename);

    char *fullname = malloc(fullname_len + 1);

    strcpy(fullname, filepath);
    strcpy(fullname + filepath_len, filename);

    fullname[fullname_len] = '\0';

    return fullname;
}

#if !defined(cider_fslash_delims)
void cider_fslash_delims(char *file)
{
    for (int i = 0; file[i]; ++i)
    {
        if (file[i] == '\\')
        {
            file[i] = '/';
        }
    }
}
#endif

#if !defined(cider_bslash_delims)
void cider_bslash_delims(char *file)
{
    do
    {
        if (*file == '/')
        {
            *file = '\\';
        }
    }
    while (*++file);
}
#endif
