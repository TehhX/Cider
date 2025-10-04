#ifndef CIDER_H
#define CIDER_H

/*
    Cider - A small library for path, directory and filename manipulation.

    Glossary (Using example /home/user/my_file.txt):
        * Extension | The type of file after the period in a file | txt
        * Filename | The name of a file including its extension | my_file.txt
        * Filepath | The absolute directory up to but excluding the filename | /home/user/
        * Fullname | The absolute directory and filepath together | /home/user/my_file.txt
        * File | A wildcard encompassing any of the above. Must make sense in contenxt, e.g cannot extract an extension from a filepath | *
*/

#if defined(_WIN32) || defined(_WIN64)
    // Centralized windows definition.
    #define CIDER_WIN 1
#endif

#ifdef CIDER_WIN
    #define CIDER_PATH_DELIM '\\'
#elif defined(__linux__)
    #define CIDER_PATH_DELIM '/'
#else
    #error Cider currently only supports Windows and Linux.
#endif

typedef const char * const __restrict __cider_str_const;
typedef       char *       __restrict __cider_str_mut;

// Returns a string containing the fullname of the current process. Malloc'd.
char *cider_exec_fullname();

// Returns the filepath extracted from a file. Delims must be system default. Modifies in place, returns a possibly realloc'd pointer to file.
char *cider_to_filepath(__cider_str_mut file);

// Returns the filename extracted from file. Delims must be system default. Modifies in place, returns a possibly realloc'd pointer to file.
char *cider_to_filename(__cider_str_mut file);

// Returns the extension extracted from file. Delims must be system default. Modifies in place, returns a possibly realloc'd pointer to file.
char *cider_to_extension(__cider_str_mut file);

#if CIDER_PATH_DELIM != '/'
    // Forward Slash Delims - Changes all instances of '\'s to '/'s. Modifies in place. Not intended for use with Cider once delims are not system default. Note: Will not do anything on systems with forward-slashes as default path delimiters.
    void cider_fslash_delims(__cider_str_mut file);
#else
    // System default is fslashes, no action.
    #define cider_fslash_delims(GARB)
#endif

#if CIDER_PATH_DELIM != '\\'
    // Back Slash Delims - Changes all instances of '/'s to '\'s. Modifies in place. Not intended for use with Cider once delims are not system default. Note: Will not do anything on systems with back-slashes as default path delimiters.
    void cider_bslash_delims(__cider_str_mut file);
#elif CIDER_PATH_DELIM != '/'
    // System default is bslashes, no action.
    #define cider_bslash_delims(GARB)
#endif

// Returns local data folder. %APPDATA% on Windows and "/etc/" on Linux.
char *cider_data_filepath();

#endif // CIDER_H
