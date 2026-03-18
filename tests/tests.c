// None of these tests are currently automated and require human review.
#include "cider.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define STR_DEF_TO_HEAP(STR) (strcpy(malloc(sizeof(STR)), STR))

#define DEFINE_TEST_FUNC static inline __attribute__((always_inline)) void

DEFINE_TEST_FUNC test_data_filepath()
{
    char *data_filepath = cider_data_filepath();

    printf("     Data filepath: \"%s\"\n", data_filepath);

    free(data_filepath);
}

DEFINE_TEST_FUNC test_exec_fullname()
{
    char *exec_fullname = cider_exec_fullname();

    printf("     Exec fullname: \"%s\"\n", exec_fullname);

    free(exec_fullname);
}

DEFINE_TEST_FUNC test_calling_filepath()
{
    char *calling_filepath = cider_calling_filepath();

    printf("  Calling filepath: \"%s\"\n", calling_filepath);

    free(calling_filepath);
}

DEFINE_TEST_FUNC test_to_filepath()
{
    char *to_filepath = cider_to_filepath(STR_DEF_TO_HEAP("/home/dir/file.txt"));

    printf("       To Filepath: \"%s\" -> \"%s\"\n", "/home/dir/file.txt", to_filepath);

    free(to_filepath);
}

DEFINE_TEST_FUNC test_to_filename()
{
    char *to_filename = cider_to_filename(STR_DEF_TO_HEAP("/home/dir/file.txt"));

    printf("       To Filename: \"%s\" -> \"%s\"\n", "/home/dir/file.txt", to_filename);

    free(to_filename);
}

DEFINE_TEST_FUNC test_to_extension()
{
    char *to_extension = cider_to_extension(STR_DEF_TO_HEAP("/home/dir/file.txt"));

    printf("      To Extension: \"%s\" -> \"%s\"\n", "/home/dir/file.txt", to_extension);

    free(to_extension);
}

DEFINE_TEST_FUNC test_construct_fullname()
{
    char *construct_fullname = cider_construct_fullname(STR_DEF_TO_HEAP("/home/dir/"), "file.txt");

    printf("Construct Fullname: \"/home/dir/\" + \"file.txt\" -> \"%s\"\n", construct_fullname);

    free(construct_fullname);
}

DEFINE_TEST_FUNC test_forward_slash_delims()
{
    char *forward_slash_delims = cider_forward_slash_delims(STR_DEF_TO_HEAP("/home/dir/file.txt"));

    printf("     FSlash Delims: \"%s\"\n", forward_slash_delims);

    free(forward_slash_delims);
}

DEFINE_TEST_FUNC test_back_slash_delims()
{
    char *back_slash_delims = cider_back_slash_delims(STR_DEF_TO_HEAP("/home/dir/file.txt"));

    printf("     BSlash Delims: \"%s\"\n", back_slash_delims);

    free(back_slash_delims);
}

int main()
{
    test_data_filepath();

    test_exec_fullname();

    test_calling_filepath();

    test_to_filepath();

    test_to_filename();

    test_to_extension();

    test_construct_fullname();

    test_forward_slash_delims();

    test_back_slash_delims();
}
