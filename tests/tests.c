// None of these tests are currently automated and require human review.
#include "cider.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "inttypes.h"

#define STR_DEF_TO_HEAP(STR) (strcpy(malloc(sizeof(STR)), STR))

#ifdef __GNUC__
    #define DEFINE_TEST_FUNC static inline __attribute__((always_inline)) void
#elif defined(_MSC_VER)
    #define DEFINE_TEST_FUNC static inline void
#else
    #error "Unknown compiler."
#endif

#define TEST_FILENAME "test_file_IGN.txt"
#define TEST_FULLNAME CIDER_PATH_DELIM_S "home" CIDER_PATH_DELIM_S "dir" CIDER_PATH_DELIM_S "file.txt"

DEFINE_TEST_FUNC test_data_filepath()
{
    char *data_filepath = cider_data_filepath();

    printf("         %*.sData filepath: \"%s\"\n", sizeof(TEST_FILENAME) - 1, "", data_filepath);

    free(data_filepath);
}

DEFINE_TEST_FUNC test_exec_fullname()
{
    char *exec_fullname = cider_exec_fullname();

    printf("         %*.sExec fullname: \"%s\"\n", sizeof(TEST_FILENAME) - 1, "", exec_fullname);

    free(exec_fullname);
}

DEFINE_TEST_FUNC test_calling_filepath()
{
    char *calling_filepath = cider_calling_filepath();

    printf("      %*.sCalling filepath: \"%s\"\n", sizeof(TEST_FILENAME) - 1, "", calling_filepath);

    free(calling_filepath);
}

DEFINE_TEST_FUNC test_to_filepath()
{
    char *to_filepath = cider_to_filepath(STR_DEF_TO_HEAP(TEST_FULLNAME));

    printf("           %*.sTo Filepath: \"%s\" -> \"%s\"\n", sizeof(TEST_FILENAME) - 1, "", TEST_FULLNAME, to_filepath);

    free(to_filepath);
}

DEFINE_TEST_FUNC test_to_filename()
{
    char *to_filename = cider_to_filename(STR_DEF_TO_HEAP(TEST_FULLNAME));

    printf("           %*.sTo Filename: \"%s\" -> \"%s\"\n", sizeof(TEST_FILENAME) - 1, "", TEST_FULLNAME, to_filename);

    free(to_filename);
}

DEFINE_TEST_FUNC test_to_extension()
{
    char *to_extension = cider_to_extension(STR_DEF_TO_HEAP(TEST_FULLNAME));

    printf("          %*.sTo Extension: \"%s\" -> \"%s\"\n", sizeof(TEST_FILENAME) - 1, "", TEST_FULLNAME, to_extension);

    free(to_extension);
}

DEFINE_TEST_FUNC test_construct_fullname()
{
    char *construct_fullname = cider_construct_fullname(STR_DEF_TO_HEAP(CIDER_PATH_DELIM_S "home" CIDER_PATH_DELIM_S "dir" CIDER_PATH_DELIM_S), "file.txt");

    printf("    %*.sConstruct Fullname: \"" CIDER_PATH_DELIM_S "home" CIDER_PATH_DELIM_S "dir" CIDER_PATH_DELIM_S "\" + \"file.txt\" -> \"%s\"\n", sizeof(TEST_FILENAME) - 1, "", construct_fullname);

    free(construct_fullname);
}

DEFINE_TEST_FUNC test_forward_slash_delims()
{
    char *forward_slash_delims = cider_forward_slash_delims(STR_DEF_TO_HEAP(TEST_FULLNAME));

    printf("         %*.sFSlash Delims: \"%s\"\n", sizeof(TEST_FILENAME) - 1, "", forward_slash_delims);

    free(forward_slash_delims);
}

DEFINE_TEST_FUNC test_back_slash_delims()
{
    char *back_slash_delims = cider_back_slash_delims(STR_DEF_TO_HEAP(TEST_FULLNAME));

    printf("         %*.sBSlash Delims: \"%s\"\n", sizeof(TEST_FILENAME) - 1, "", back_slash_delims);

    free(back_slash_delims);
}

DEFINE_TEST_FUNC test_canonicalize_file()
{
    char *canonicalized_fullname = cider_canonicalize_file(TEST_FILENAME);

    printf("     %*.sTo canon fullname: \"%s\"\n", sizeof(TEST_FILENAME) - 1, "", canonicalized_fullname);

    free(canonicalized_fullname);
}

DEFINE_TEST_FUNC test_creation_date_file()
{
    printf("Creation E-seconds of " TEST_FILENAME ": %" PRIu32 "\n", cider_creation_date_file(TEST_FILENAME));
}

int main()
{
    // Some functions require a test file
    FILE *test_file = fopen(TEST_FILENAME, "w");
    if (NULL == test_file)
    {
        goto SYSTEM_FAIL;
    }
    else
    {
        fputs("This is a testing file.\n", test_file);
    }

    test_data_filepath();

    test_exec_fullname();

    test_calling_filepath();

    test_to_filepath();

    test_to_filename();

    test_to_extension();

    test_construct_fullname();

    test_forward_slash_delims();

    test_back_slash_delims();

    test_canonicalize_file();

    test_creation_date_file();

    if (fclose(test_file))
    {
        goto SYSTEM_FAIL;
    }

    return 0;
    SYSTEM_FAIL:

    perror("System fail during test_creation_date_file()");
    return 1;
}
