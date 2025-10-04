#include "../src/cider.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define copy(STR) strcpy(calloc(strlen(STR) + 1, 1), STR)

int main()
{
    char *exec_fullname = cider_exec_fullname();
    printf("Exec fullname: %s\n", exec_fullname);

    char *exec_filepath = cider_to_filepath(copy(exec_fullname));
    printf("Exec filepath: %s\n", exec_filepath);
    free(exec_filepath);

    char *exec_filename = cider_to_filename(copy(exec_fullname));
    printf("Exec filename: %s\n", exec_filename);
    free(exec_filename);

    char *exec_extension = cider_to_extension(copy(exec_fullname));
    printf("Exec extension: %s\n", exec_extension ? exec_extension : "COFF, no extension.");
    free(exec_extension);

    char *exec_fullname_2 = copy(exec_fullname);
    cider_fslash_delims(exec_fullname_2);
    printf("Exec with '\\'s replaced by '/'s: %s\n", exec_fullname_2);
    free(exec_fullname_2);

    cider_bslash_delims(copy(exec_fullname));
    printf("Exec with '/'s replaced by '\\'s: %s\n", exec_fullname);
    free(exec_fullname);
}
