#ifndef CIDER_H
#define CIDER_H

/*
    Cider - A small library for path, directory and filename manipulation. Contains various cross-platform utilities in the same realm
        * Supported OS's:
            *   Linux |                             Tested each commit on Arch x64
            * Windows | Rarely tested, sometimes functions are left un-implemented
        * Find functions below
        * Report issues, contribute etc at https://github.com/TehhX/Cider

    File related glossary (Using example /home/user/my_file.txt):
        * Extension |                                          The type of file after the period in a file. |                    txt
        *  Filename |                                           The name of a file including its extension. |            my_file.txt
        *  Filepath |                              The absolute directory up to but excluding the filename. | /home/user/
        *  Fullname |                                         The absolute directory and filepath together. | /home/user/my_file.txt
        *  Seminame |  The filename with any amount of preceding directories which don't make it a fullname |       user/my_file.txt
        *      File |                 A wildcard encompassing any of the above. Must make sense in context. | ??????????????????????

    Misc glossary:
        * UE-seconds | The amount of seconds since the UNIX epoch
*/

#define CIDER_PLAT_LIN 0 // Linux
#define CIDER_PLAT_WIN 1 // Windows

// Platform specific
#if defined(_WIN32) || defined(_WIN64)
    #define CIDER_PLATFORM CIDER_PLAT_WIN
    #define CIDER_PATH_DELIM_S "\\"
    #define CIDER_PATH_DELIM_C '\\'
#elif defined(__linux__)
    #define CIDER_PLATFORM CIDER_PLAT_LIN
    #define CIDER_PATH_DELIM_S "/"
    #define CIDER_PATH_DELIM_C '/'
#else
    #error Cider currently only supports Windows and Linux. Comment this line out if you want to test another platform
#endif

// Compiler specific
#ifdef __GNUC__
    #define CIDER_ATTR_MALLOC __attribute__((malloc))
    #define CIDER_EXTERN extern
#elif defined(_MSC_VER)
    #define CIDER_ATTR_MALLOC __declspec(noalias) __declspec(restrict)

    #ifdef CIDER_EXPORT
        #define CIDER_EXTERN __declspec(dllexport)
    #else
        #define CIDER_EXTERN __declspec(dllimport)
    #endif
#else
    #error "Unknown compiler."
#endif

#include "stdint.h"

// @brief Returns malloc'd string containing the filepath of the local data folder. This will be %appdata%\ on Windows, and $HOME/.local/share/ on Linux
CIDER_ATTR_MALLOC CIDER_EXTERN char *cider_data_filepath();

// @brief Returns malloc'd string containing the fullname of the current process
CIDER_ATTR_MALLOC CIDER_EXTERN char *cider_exec_fullname();

// @brief Returns malloc'd string containing the filepath of the calling directory
CIDER_ATTR_MALLOC CIDER_EXTERN char *cider_calling_filepath();

/*
    @brief Returns filepath extracted from `file`. Modifies in place

        @param file The file from which to extract a filepath

        @returns Possibly reallocated `file` or NULL if error/filepath does not exist in `file`

        @warning `file` MUST be malloc'd
        @warning `file` path delimiters MUST be system default
*/
CIDER_EXTERN char *cider_to_filepath(char *file);

/*
    @brief Returns the filename extracted from `file`. Modifies in place

        @param file The file from which to extract a filename

        @returns Possibly reallocated `file` now containing the filepath, or NULL if error/filename does not exist in `file`

        @warning `file` MUST be malloc'd
        @warning `file` path delimiters MUST be system default
*/
CIDER_EXTERN char *cider_to_filename(char *file);

/*
    @brief Returns the extension extracted from `file`. Modifies in place

        @param file The file from which to extract an extension

        @returns Possibly reallocated `file` now containing the filename, or NULL if error/extension does not exist in `file`

        @warning `file` MUST be malloc'd
        @warning `file` path delimiters MUST be system default
*/
CIDER_EXTERN char *cider_to_extension(char *file);

/*
    @brief Returns a fullpath constructed from a provided filepath and filename. Modifies in place

        @param filepath The filepath onto which `filename` will be appended
        @param filename The filename to append to `filepath`

        @returns Reallocated `filepath` now containing the fullname

        @warning `filepath` MUST be malloc'd

        @note Essentially a fancy strcat
*/
CIDER_EXTERN char *cider_construct_fullname(char *filepath, const char *filename);

/*
    @brief Returns malloc'd string containing canonical fullname of file

        @param file The file to canonicalize

        @returns Malloc'd canonical fullname of `file`

        @warning May still be bugs to iron out on Linux
*/
CIDER_ATTR_MALLOC CIDER_EXTERN char *cider_canonicalize_file(const char *file);

// @brief Returns the creation date of file in UE-seconds
CIDER_EXTERN uint32_t cider_creation_date_file(const char *file);

/*
    @brief Resets all occurrences of `to_reset` in `path` to default path delimiter. Modifies in place

        @param path The path to replace delimiters of
        @param to_reset The character to replace instances of

        @returns Modified `path`

        @warning This will replace all occurrences of `to_reset`, even those you may not want replaced
*/
CIDER_EXTERN char *cider_reset_delims(char *path, char to_reset);

#if CIDER_PATH_DELIM_C != '/'
    // Forward Slash Delims - Changes all instances of '\'s to '/'s. Modifies in place and returns file. Not intended for use with Cider once delims are not system default. Will not do anything on systems with forward-slashes as default path delimiters. This system uses forward-slash delimiters, so no action is taken
    CIDER_EXTERN char *cider_forward_slash_delims(char *const file);
#else
    // Forward Slash Delims - Changes all instances of '\'s to '/'s. Modifies in place and returns file. Not intended for use with Cider once delims are not system default. Will not do anything on systems with forward-slashes as default path delimiters. This system does NOT use forward-slash delimiters, so they are changed to forward-slashes
    #define cider_forward_slash_delims(file) file
#endif

#if CIDER_PATH_DELIM_C != '\\'
    // Back Slash Delims - Changes all instances of '/'s to '\'s. Modifies in place and returns file. Not intended for use with Cider once delims are not system default. Will not do anything on systems with back-slashes as default path delimiters. This system does NOT use back-slash delimiters, so they are changed to back-slashes
    CIDER_EXTERN char *cider_back_slash_delims(char *const file);
#else
    // Back Slash Delims - Changes all instances of '/'s to '\'s. Modifies in place and returns file. Not intended for use with Cider once delims are not system default. Will not do anything on systems with back-slashes as default path delimiters. This system uses back-slash delimiters, so no action is taken
    #define cider_back_slash_delims(file) file
#endif

#undef CIDER_ATTR_MALLOC

#endif // CIDER_H
