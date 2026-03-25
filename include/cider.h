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

#if defined(_WIN32) || defined(_WIN64)
    #define CIDER_PLATFORM PLAT_WIN
    #define CIDER_PATH_DELIM '\\'
#elif defined(__linux__)
    #define CIDER_PLATFORM CIDER_PLAT_LIN
    #define CIDER_PATH_DELIM '/'
#else
    #error Cider currently only supports Windows and Linux. Comment this line out if you want to test another platform
#endif

#include "stdint.h"

// Returns malloc'd string containing the filepath of the local data folder. This will be %appdata%\ on Windows, and $HOME/.local/share/ on Linux
extern char *cider_data_filepath() __attribute__((malloc));

// Returns malloc'd string containing the fullname of the current process
extern char *cider_exec_fullname() __attribute__((malloc));

// Returns malloc'd string containing the filepath of the calling directory
extern char *cider_calling_filepath() __attribute__((malloc));

// Returns the filepath extracted from a file. 'file' must be malloc'd. Delims must be system default. Modifies in place, returns a possibly realloc'd pointer to file. Returns NULL if one does not exist in file
extern char *cider_to_filepath(char *file);

// Returns the filename extracted from file. 'file' must be malloc'd. Delims must be system default. Modifies in place, returns a possibly realloc'd pointer to file. Returns NULL if one does not exist in file
extern char *cider_to_filename(char *file);

// Returns the extension extracted from file. 'file' must be malloc'd. Delims must be system default. Modifies in place, returns a possibly realloc'd pointer to file. Returns NULL if one does not exist in file
extern char *cider_to_extension(char *file);

// Returns a fullpath constructed from a provided filepath and filename. filepath must be malloc'd. Modifies in place, returns a possibly realloc'd pointer to filepath. Essentially a fancy strcat
extern char *cider_construct_fullname(char *filepath, const char *filename);

// Returns a canonical file from a provided file. Will NOT work with non-existent files
extern char *cider_canonicalize_file(const char *file);

// Returns the creation date of file in UE-seconds
extern uint32_t cider_creation_date_file(const char *file);

#if CIDER_PATH_DELIM != '/'
    // Forward Slash Delims - Changes all instances of '\'s to '/'s. Modifies in place and returns file. Not intended for use with Cider once delims are not system default. Will not do anything on systems with forward-slashes as default path delimiters. This system uses forward-slash delimiters, so no action is taken
    extern char *cider_forward_slash_delims(char *const file);
#else
    // Forward Slash Delims - Changes all instances of '\'s to '/'s. Modifies in place and returns file. Not intended for use with Cider once delims are not system default. Will not do anything on systems with forward-slashes as default path delimiters. This system does NOT use forward-slash delimiters, so they are changed to forward-slashes
    #define cider_forward_slash_delims(file) file
#endif

#if CIDER_PATH_DELIM != '\\'
    // Back Slash Delims - Changes all instances of '/'s to '\'s. Modifies in place and returns file. Not intended for use with Cider once delims are not system default. Will not do anything on systems with back-slashes as default path delimiters. This system does NOT use back-slash delimiters, so they are changed to back-slashes
    extern char *cider_back_slash_delims(char *const file);
#else
    // Back Slash Delims - Changes all instances of '/'s to '\'s. Modifies in place and returns file. Not intended for use with Cider once delims are not system default. Will not do anything on systems with back-slashes as default path delimiters. This system uses back-slash delimiters, so no action is taken
    #define cider_back_slash_delims(file) file
#endif

#endif // CIDER_H
