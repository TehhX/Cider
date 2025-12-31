#ifndef CIDER_H
#define CIDER_H

/*
    Cider - A small library for path, directory and filename manipulation.

    Glossary (Using example /home/user/my_file.txt):
        * Extension | The type of file after the period in a file | txt
        * Filename | The name of a file including its extension | my_file.txt
        * Filepath | The absolute directory up to but excluding the filename | /home/user/
        * Fullname | The absolute directory and filepath together | /home/user/my_file.txt
        * File | A wildcard encompassing any of the above. Must make sense in context, e.g cannot extract an extension from a filepath | *
*/

#define CIDER_PLAT_LIN 0 // Linux
#define CIDER_PLAT_WIN 1 // Windows

#if defined(_WIN32) || defined(_WIN64)
    #define CIDER_PLATFORM PLAT_WIN
    #define CIDER_PATH_DELIM '\\'
#elif defined(__linux__)
    #define CIDER_PLATFORM PLAT_LIN
    #define CIDER_PATH_DELIM '/'
#else
    #error Cider currently only supports Windows and Linux. Comment this line out if you want to test another platform.
#endif

typedef const char * const __restrict __cider_str_const;
typedef       char *       __restrict __cider_str_mut;

// Returns malloc'd local data folder. %APPDATA% on Windows and "/etc/" on Linux.
extern char *cider_data_filepath();

// Returns a string containing the fullname of the current process. Malloc'd.
extern char *cider_exec_fullname();

// Returns the filepath extracted from a file. Delims must be system default. Modifies in place, returns a possibly realloc'd pointer to file. Returns NULL if one does not exist in file.
extern char *cider_to_filepath(__cider_str_mut file);

// Returns the filename extracted from file. Delims must be system default. Modifies in place, returns a possibly realloc'd pointer to file. Returns NULL if one does not exist in file.
extern char *cider_to_filename(__cider_str_mut file);

// Returns the extension extracted from file. Delims must be system default. Modifies in place, returns a possibly realloc'd pointer to file. Returns NULL if one does not exist in file.
extern char *cider_to_extension(__cider_str_mut file);

// Returns a string containing a fullpath constructed from a provided filepath and filename. Malloc'd.
extern char *cider_construct_fullname(__cider_str_const filepath, __cider_str_const filename);

#if CIDER_PATH_DELIM != '/'
    // Forward Slash Delims - Changes all instances of '\'s to '/'s. Modifies in place. Not intended for use with Cider once delims are not system default. Note: Will not do anything on systems with forward-slashes as default path delimiters.
    extern void cider_fslash_delims(__cider_str_mut file);
#else
    // System default is fslashes, no action.
    #define cider_fslash_delims(GARB)
#endif

#if CIDER_PATH_DELIM != '\\'
    // Back Slash Delims - Changes all instances of '/'s to '\'s. Modifies in place. Not intended for use with Cider once delims are not system default. Note: Will not do anything on systems with back-slashes as default path delimiters.
    extern void cider_bslash_delims(__cider_str_mut file);
#elif CIDER_PATH_DELIM != '/'
    // System default is bslashes, no action.
    #define cider_bslash_delims(GARB)
#endif

#endif // CIDER_H
