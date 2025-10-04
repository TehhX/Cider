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

char *cider_to_filepath(__cider_instr_const file)
{
    const int file_len = strlen(file);

    for (int i = file_len - 1; i >= 0; --i)
    {
        if (file[i] == CIDER_PATH_DELIM)
        {
            const int filepath_len = i + 2;
            char *filepath = malloc(filepath_len);
            filepath[filepath_len - 1] = 0;
            return memcpy(filepath, file, filepath_len - 1);
        }
    }

    // No delim detected, return 0:
    return 0;
}

char *cider_to_filename(__cider_instr_const file)
{
    const int file_len = strlen(file);

    for (int i = file_len; i >= 0; --i)
    {
        if (file[i] == CIDER_PATH_DELIM)
        {
            const int filename_len = file_len - i;
            char *filename = malloc(filename_len);
            filename[filename_len - 1] = 0;
            return memcpy(filename, file + i + 1, filename_len - 1);
        }
    }

    // No delim detected, return 0:
    return 0;
}

char *cider_to_extension(__cider_instr_const file)
{
    const int file_len = strlen(file);

    for (int i = file_len; i >= 0; --i)
    {
        if (file[i] == '.')
        {
            const int extension_len = file_len - i;
            char *extension = malloc(extension_len);
            extension[extension_len - 1] = 0;
            return memcpy(extension, file + i + 1, extension_len - 1);
        }
    }

    // No delim detected, return 0:
    return 0;
}

#if !defined(cider_fslash_delims)
void cider_fslash_delims(__cider_instr_mut file)
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
void cider_bslash_delims(__cider_instr_mut file)
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
