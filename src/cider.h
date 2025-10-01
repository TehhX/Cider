#ifndef CIDER_H
#define CIDER_H

/*
    Cider - A small library for path, directory and filename manipulation. Currently, all functions return a malloc'd value which must be freed by the end user, or NULL if something went wrong.

    Glossary (Using example /home/user/my_file.txt):
        * Extension | The type of file after the period in a file | txt
        * Filename | The name of a file including its extension | my_file.txt
        * Filepath | The absolute directory up to but excluding the filename | /home/user/
        * Fullname | The absolute directory and filepath together | /home/user/my_file.txt
        * File | A wildcard encompassing any of the above. Must make sense in contenxt, e.g cannot extract an extension from a filepath | *
*/

#define __cider_instr const char*const restrict

// Exec Fullname - Returns a string containing the fullname of the current process.
char *cider_exec_fullname();

// To Filepath - Returns the filepath extracted from a file.
char *cider_to_filepath(__cider_instr file);

// To Filename - Returns the filename extracted from file.
char *cider_to_filename(__cider_instr file);

// To Extension - Returns the extension extracted from file.
char *cider_to_extension(__cider_instr file);

// Forward Slash Delims - Changes all instances of '\'s to '/'s.
char *cider_fslash_delims(__cider_instr file);

// Back Slash Delims - Changes all instances of '/'s to '\'s.
char *cider_bslash_delims(__cider_instr file);

#endif // CIDER_H
