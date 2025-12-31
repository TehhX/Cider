/*
    TODO:
        * Add debugging tools, error handling
*/
#include "cider.h"

#if CIDER_PLATFORM == CIDER_PLAT_WIN
    #include "libloaderapi.h" // For GetModuleFileNameA(...)
    #ifndef PATH_MAX
        #include "minwindef.h" // Contains MAX_PATH
        #define PATH_MAX MAX_PATH
    #endif
#endif

#if CIDER_PLATFORM == CIDER_PLAT_LIN
    #include "linux/limits.h" // For PATH_MAX
    #include "unistd.h" // For readlink(...)
#endif

#include "stdlib.h"
#include "string.h"

char *cider_exec_fullname()
{
    char * const fullpath = malloc(PATH_MAX + 1);
    const int fullpath_len =
#if CIDER_PLATFORM == CIDER_PLAT_LIN
    readlink("/proc/self/exe", fullpath, PATH_MAX) + 1;
#elif CIDER_PLATFORM == CIDER_PLAT_WIN
    GetModuleFileNameA(0, fullpath, PATH_MAX) + 1;
#endif
    fullpath[fullpath_len - 1] = 0;
    return realloc(fullpath, fullpath_len);
}

char *cider_to_filepath(__cider_str_mut file)
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

char *cider_to_filename(__cider_str_mut file)
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

char *cider_to_extension(__cider_str_mut file)
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

#if !defined(cider_fslash_delims)
void cider_fslash_delims(__cider_str_mut file)
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
void cider_bslash_delims(__cider_str_mut file)
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

char *cider_data_filepath()
{
#if CIDER_PLATFORM == CIDER_PLAT_WIN
    char *appdata_table = getenv("APPDATA");
    const int filepath_len = strlen(appdata_table);

    char *filepath = strcpy(malloc(filepath_len + 2), filepath);

    filepath[filepath_len] = CIDER_PATH_DELIM;
    filepath[filepath_len + 1] = 0;
#elif CIDER_PLATFORM == CIDER_PLAT_LIN
    return strcpy(malloc(sizeof("~/")), "~/");
#endif
}
