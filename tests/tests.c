// None of these tests are currently automated, and must be reviewed by a human.

#include "cider.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

static inline char *copy_str(const char *const input)
{
    const int input_len = strlen(input);
    return memcpy(malloc(input_len + 1), input, input_len + 1);
}

int main()
{
    char *exec_fullname = cider_exec_fullname();
    printf("Exec fullname: %s\n", exec_fullname);

    char *exec_filepath = cider_to_filepath(copy_str(exec_fullname));
    printf("Exec filepath: %s\n", exec_filepath);

    char *exec_filename = cider_to_filename(copy_str(exec_fullname));
    printf("Exec filename: %s\n", exec_filename);

    char *exec_fullname_2 = cider_construct_fullname(exec_filepath, exec_filename);
    printf("Exec constructed fullname: %s\n", exec_fullname_2);
    free(exec_filepath);
    free(exec_fullname_2);

    char *exec_fullname_3 = copy_str(exec_fullname);
    char *exec_extension = cider_to_extension(exec_fullname_3);
    printf("Exec extension: %s\n", exec_extension == NULL ? "None" : exec_extension);
    free(exec_extension);
    free(exec_fullname_3);

    char *exec_fullname_4 = copy_str(exec_fullname);
    cider_fslash_delims(exec_fullname_4);
    printf("Exec with '\\'s replaced by '/'s: %s\n", exec_fullname_4);
    free(exec_fullname_4);

    cider_bslash_delims(exec_fullname);
    printf("Exec with '/'s replaced by '\\'s: %s\n", exec_fullname);
    free(exec_fullname);

    char *data_filepath = cider_data_filepath();
    printf("Data path: %s\n", data_filepath);

    char *data_fullname = cider_construct_fullname(data_filepath, exec_filename);
    printf("Data fullname with exec: %s\n", data_fullname);
    free(exec_filename);
    free(data_filepath);
    free(data_fullname);
}
