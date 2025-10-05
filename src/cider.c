/*
    TODO:
        * Add debugging tools, error handling
*/
#include "cider.h"

#ifdef CIDER_WIN
    #include "libloaderapi.h" // For GetModuleFileNameA(...)
    #ifndef PATH_MAX
        #include "minwindef.h" // Contains MAX_PATH
        #define PATH_MAX MAX_PATH
    #endif
#elif defined(__linux__)
    #include "linux/limits.h" // For PATH_MAX
    #include "unistd.h" // For readlink(...)
#endif

#include "stdlib.h"
#include "string.h"

char *cider_exec_fullname()
{
    char * const fullpath = malloc(PATH_MAX + 1);
    const int fullpath_len =
#ifdef __linux__
    readlink("/proc/self/exe", fullpath, PATH_MAX) + 1;
#elif defined(CIDER_WIN)
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
            file[i + 1] = 0;
            return realloc(file, i + 2);
        }
    }
    return 0;
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
    return 0;
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
    return 0;
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
    } while (*++file);
}
#endif

char *cider_data_filepath()
{
    char *filepath =
#ifdef CIDER_WIN
    getenv("APPDATA");

    const int filepath_len = strlen(filepath);

    filepath = strcpy(malloc(filepath_len + 2), filepath);
    filepath[filepath_len] = CIDER_PATH_DELIM;
    filepath[filepath_len + 1] = 0;
#elif defined(__linux__)
    strcpy(malloc(sizeof("/etc/")), "/etc/");
#endif
    return filepath;
}
