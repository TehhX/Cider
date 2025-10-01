/*
    TODO:
        * Add debugging tools, error handling
*/

#include "cider.h"

#include "stdlib.h"
#include "string.h"

#if defined(_WIN32) || defined(_WIN64)
    #define __cider_win 1
#endif

#if defined(__cider_win)
    #define __cider_path_delim '\\'
    #include "libloaderapi.h" // For GetModuleFileNameA(...)
    #ifndef PATH_MAX
        #include "minwindef.h" // Contains MAX_PATH
        #define PATH_MAX MAX_PATH
    #endif
#elif defined(__linux__)
    #include "linux/limits.h" // For PATH_MAX
    #include "unistd.h" // For readlink(...)
    #define __cider_path_delim '/'
#else
    #error Cider currently only supports Windows and Linux.
#endif

char *cider_exec_fullname()
{
    char *fullpath = malloc(PATH_MAX + 1);
    const int fullpath_len =
#ifdef __linux__
    readlink("/proc/self/exe", fullpath, PATH_MAX) + 1;
#elifdef __cider_win
    GetModuleFileNameA(0, fullpath, PATH_MAX) + 1;
#endif
    fullpath[fullpath_len - 1] = 0;
    return realloc(fullpath, fullpath_len);
}

char *cider_to_filepath(__cider_instr file)
{
    const int file_len = strlen(file);

    for (int i = file_len - 1; i >= 0; --i)
    {
        if (file[i] == __cider_path_delim)
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

char *cider_to_filename(__cider_instr file)
{
    const int file_len = strlen(file);

    for (int i = file_len; i >= 0; --i)
    {
        if (file[i] == __cider_path_delim)
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

char *cider_to_extension(__cider_instr file)
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

char *cider_fslash_delims(__cider_instr file)
{
    const int file_len = strlen(file) + 1;
    char *file_copy = memcpy(malloc(file_len), file, file_len);

    for (int i = 0; i < file_len - 1; ++i)
    {
        if (file_copy[i] == '\\')
        {
            file_copy[i] = '/';
        }
    }

    return file_copy;
}

char *cider_bslash_delims(__cider_instr file)
{
    const int file_len = strlen(file) + 1;
    char *file_copy = memcpy(malloc(file_len), file, file_len);

    for (int i = 0; i < file_len - 1; ++i)
    {
        if (file_copy[i] == '/')
        {
            file_copy[i] = '\\';
        }
    }

    return file_copy;
}
