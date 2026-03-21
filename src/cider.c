#include "cider.h"

#include "stdlib.h"
#include "string.h"

#include "stdio.h" // REMOVE

#define CIDER_PLAT_WIN_INSERT(CONTENT)
#define CIDER_PLAT_LIN_INSERT(CONTENT)

#if CIDER_PLATFORM == CIDER_PLAT_WIN
    #undef CIDER_PLAT_WIN_INSERT
    #define CIDER_PLAT_WIN_INSERT(CONTENT) CONTENT

    #include "libloaderapi.h" // For GetModuleFileNameA(...)

    #ifndef PATH_MAX
        #include "minwindef.h" // Contains MAX_PATH
        #define PATH_MAX MAX_PATH
    #endif
#elif CIDER_PLATFORM == CIDER_PLAT_LIN
    #undef CIDER_PLAT_LIN_INSERT
    #define CIDER_PLAT_LIN_INSERT(CONTENT) CONTENT

    #include "linux/limits.h" // For PATH_MAX
    #include "unistd.h" // For readlink(...)
#endif

char *cider_data_filepath()
{
    char *data_filepath =
        CIDER_PLAT_WIN_INSERT(getenv("APPDATA"))
        CIDER_PLAT_LIN_INSERT(getenv("HOME"))
    ;

    const int data_filepath_len = strlen(data_filepath);

    CIDER_PLAT_LIN_INSERT
    (
        const char local_share[] = "/.local/share/";
        data_filepath = memcpy(malloc(data_filepath_len + sizeof(local_share)), data_filepath, data_filepath_len);
        memcpy(data_filepath + data_filepath_len, local_share, sizeof(local_share));
    )

    CIDER_PLAT_WIN_INSERT
    (
        data_filepath = strcpy(malloc(data_filepath_len + 2), data_filepath);
        data_filepath[data_filepath_len] = CIDER_PATH_DELIM;
        data_filepath[data_filepath_len + 1] = 0;
    )

    return data_filepath;
}

char *cider_exec_fullname()
{
    char *const exec_fullname = malloc(PATH_MAX + 1);

    const int exec_fullname_len =
        CIDER_PLAT_WIN_INSERT(GetModuleFileNameA(0, exec_fullname, PATH_MAX) + 1)
        CIDER_PLAT_LIN_INSERT(readlink("/proc/self/exe", exec_fullname, PATH_MAX) + 1)
    ;

    exec_fullname[exec_fullname_len - 1] = 0;
    return realloc(exec_fullname, exec_fullname_len);
}

#if CIDER_PLATFORM != CIDER_PLAT_LIN
    // TODO: Implement cider_calling_filepath for Windows etc
    #error cider_calling_filepath() not yet implemented for platforms other than Linux.
#endif
char *cider_calling_filepath()
{
    char *calling_filepath = malloc(PATH_MAX);
    getcwd(calling_filepath, PATH_MAX);

    // Length of the filepath includes '/'. getcwd returns sans '/'
    const int calling_filepath_len = strlen(calling_filepath) + 1;
    calling_filepath = realloc(calling_filepath, calling_filepath_len + 1);

    calling_filepath[calling_filepath_len - 1] = CIDER_PATH_DELIM;
    calling_filepath[calling_filepath_len] = '\0';

    return calling_filepath;
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
        // Delim found before '.', no extension
        if (file[i] == CIDER_PATH_DELIM)
        {
            return NULL;
        }
        // '.' found, return what's after it
        else if (file[i] == '.')
        {
            memmove(file, file + i + 1, file_len - i);
            return realloc(file, file_len - i);
        }
    }
}

char *cider_construct_fullname(char *filepath, const char *filename)
{
    return strcat(realloc(filepath, strlen(filepath) + strlen(filename) + 2), filename);
}

#if CIDER_PLATFORM != CIDER_PLAT_LIN
    // TODO: Implement cider_canonicalize_file for Windows etc
    #error cider_canonicalize_file() not yet implemented for platforms other than Linux.
#endif
char *cider_canonicalize_file(const char *file)
{
    // TODO: Make work for non-existent files
    return realpath(file, NULL);
}

#if !defined(cider_forward_slash_delims)
    char *cider_forward_slash_delims(char *const file)
    {
        for (int i = 0; file[i]; ++i)
        {
            if (file[i] == CIDER_PATH_DELIM)
            {
                file[i] = '/';
            }
        }

        return file;
    }
#endif

#if !defined(cider_back_slash_delims)
    char *cider_back_slash_delims(char *const file)
    {
        for (int i = 0; file[i]; ++i)
        {
            if (file[i] == CIDER_PATH_DELIM)
            {
                file[i] = '\\';
            }
        }

        return file;
    }
#endif
