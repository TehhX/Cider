#include "cider.h"

#include "stdlib.h"
#include "string.h"

#define CIDER_PLAT_WIN_INSERT(CONTENT)
#define CIDER_PLAT_LIN_INSERT(CONTENT)

#if CIDER_PLATFORM == CIDER_PLAT_WIN
    #undef CIDER_PLAT_WIN_INSERT
    #define CIDER_PLAT_WIN_INSERT(CONTENT) CONTENT

    #include "windows.h"

    #ifndef PATH_MAX
        #define PATH_MAX MAX_PATH
    #endif
#elif CIDER_PLATFORM == CIDER_PLAT_LIN
    #undef CIDER_PLAT_LIN_INSERT
    #define CIDER_PLAT_LIN_INSERT(CONTENT) CONTENT

    #include "linux/limits.h" // For PATH_MAX
    #include "unistd.h" // For readlink(...)
    #include "sys/stat.h" // For struct stat
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
        data_filepath[data_filepath_len] = CIDER_PATH_DELIM_C;
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

char *cider_calling_filepath()
{
    char* calling_filepath =
        CIDER_PLAT_LIN_INSERT(getcwd(NULL, 0);)
        CIDER_PLAT_WIN_INSERT(malloc(PATH_MAX);)
    ;

    // Length of the filepath includes '/'. getcwd returns sans '/'
    CIDER_PLAT_WIN_INSERT
    (
        const int calling_filepath_len = GetCurrentDirectoryA(PATH_MAX, calling_filepath) + 1;
        calling_filepath = realloc(calling_filepath, calling_filepath_len);
    )

    CIDER_PLAT_LIN_INSERT(const int calling_filepath_len = strlen(calling_filepath) + 1);
    calling_filepath = realloc(calling_filepath, calling_filepath_len + 1);

    calling_filepath[calling_filepath_len - 1] = CIDER_PATH_DELIM_C;
    calling_filepath[calling_filepath_len] = '\0';

    return calling_filepath;
}

char *cider_to_filepath(char *file)
{
    const int file_len = strlen(file);

    for (int i = file_len - 1; i >= 0; --i)
    {
        if (file[i] == CIDER_PATH_DELIM_C)
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
        if (file[i] == CIDER_PATH_DELIM_C)
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
        if (file[i] == CIDER_PATH_DELIM_C)
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

    return NULL;
}

char *cider_construct_fullname(char *filepath, const char *const filename)
{
    return strcat(realloc(filepath, strlen(filepath) + strlen(filename) + 2), filename);
}

char *cider_canonicalize_file(const char *const file)
{
CIDER_PLAT_LIN_INSERT
(
    char *current = strcpy(malloc(strlen(file) + 1), file);
    char *rp_return;

    size_t removed_elements_len = 0;
    char **removed_elements = NULL;

    while (!(rp_return = realpath(current, NULL)))
    {
        const size_t end_i = strlen(current);
        size_t delim_i = end_i - 1;

        for (; delim_i != SIZE_MAX && current[delim_i] != CIDER_PATH_DELIM_C; --delim_i);

        if (delim_i == SIZE_MAX)
        {
            char *return_fullname = cider_construct_fullname(cider_calling_filepath(), current);

            for (size_t rem_i = removed_elements_len - 1; rem_i != SIZE_MAX; --rem_i)
            {
                strcat((return_fullname = realloc(return_fullname, strlen(return_fullname) + strlen(removed_elements[rem_i]) + 1)), removed_elements[rem_i]);
                free(removed_elements[rem_i]);
            }

            free(rp_return);
            free(current);

            free(removed_elements);

            return return_fullname;
        }

        removed_elements = reallocarray(removed_elements, ++removed_elements_len, sizeof(char *));
        strcpy((removed_elements[removed_elements_len - 1] = malloc(end_i - delim_i + 1)), current + delim_i)[end_i - delim_i] = '\0';

        current[delim_i] = '\0';

        free(rp_return);
    }

    for (size_t rem_i = removed_elements_len - 1; rem_i != SIZE_MAX; --rem_i)
    {
        strcat((rp_return = realloc(rp_return, strlen(rp_return) + strlen(removed_elements[rem_i]) + 1)), removed_elements[rem_i]);
        free(removed_elements[rem_i]);
    }

    free(current);
    free(removed_elements);

    return rp_return;
)

CIDER_PLAT_WIN_INSERT
(
    return _fullpath(NULL, file, PATH_MAX);
)

    return NULL;
}

uint32_t cider_creation_date_file(const char *const file)
{
CIDER_PLAT_LIN_INSERT
(
    struct stat file_attributes;

    if (!stat(file, &file_attributes))
    {
        return file_attributes.st_ctim.tv_sec;
    }
)

#if CIDER_PLATFORM == CIDER_PLAT_WIN
    HANDLE file_handle = CreateFileA(file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (file_handle == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    FILETIME creation_filetime;

    if (!GetFileTime(file_handle, &creation_filetime, NULL, NULL))
    {
        printf("wow2\n");
        return 0;
    }

    LARGE_INTEGER storage =
    {
        .LowPart = creation_filetime.dwLowDateTime,
        .HighPart = creation_filetime.dwHighDateTime
    };

    return (storage.QuadPart - 0x019DB1DED53E8000) / 10000000;
#endif // CIDER_PLATFORM == CIDER_PLAT_WIN

    return 0;
}

char *cider_reset_delims(char *path, const char to_reset)
{
    for (int i = 0; path[i] != '\0'; ++i)
    {
        if (path[i] == to_reset)
        {
            path[i] = CIDER_PATH_DELIM_C;
        }
    }

    return path;
}

#if !defined(cider_forward_slash_delims)
    char *cider_forward_slash_delims(char *const file)
    {
        for (int i = 0; file[i]; ++i)
        {
            if (file[i] == CIDER_PATH_DELIM_C)
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
            if (file[i] == CIDER_PATH_DELIM_C)
            {
                file[i] = '\\';
            }
        }

        return file;
    }
#endif
