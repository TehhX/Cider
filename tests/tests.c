// None of these tests are currently automated and require human review.
#include "cider.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "inttypes.h"

#define STR_DEF_TO_HEAP(STR) (strcpy(malloc(sizeof(STR)), STR))

#ifdef __GNUC__
    #define DEFINE_TEST_FUNC __attribute__((always_inline)) static inline void
#elif defined(_MSC_VER)
    #define DEFINE_TEST_FUNC __forceinline static inline void
#else
    #error "Unknown compiler."
#endif

#define REAL_FILENAME "real_file_IGN.txt"
#define REAL_FILENAME_INDENT ((int) (sizeof(REAL_FILENAME) - 1)), ""
#define FAKE_FILENAME ".././tests/../fake_folder/fake_file.txt"
#define TEST_FULLNAME CIDER_PATH_DELIM_S "home" CIDER_PATH_DELIM_S "dir" CIDER_PATH_DELIM_S "file.txt"

DEFINE_TEST_FUNC test_data_filepath()
{
    char *data_filepath = cider_data_filepath();

    printf("         %*.sData filepath: \"%s\"\n", REAL_FILENAME_INDENT, data_filepath);

    free(data_filepath);
}

DEFINE_TEST_FUNC test_exec_fullname()
{
    char *exec_fullname = cider_exec_fullname();

    printf("         %*.sExec fullname: \"%s\"\n", REAL_FILENAME_INDENT, exec_fullname);

    free(exec_fullname);
}

DEFINE_TEST_FUNC test_calling_filepath()
{
    char *calling_filepath = cider_calling_filepath();

    printf("      %*.sCalling filepath: \"%s\"\n", REAL_FILENAME_INDENT, calling_filepath);

    free(calling_filepath);
}

DEFINE_TEST_FUNC test_to_filepath()
{
    char *to_filepath = cider_to_filepath(STR_DEF_TO_HEAP(TEST_FULLNAME));

    printf("           %*.sTo Filepath: \"%s\" -> \"%s\"\n", REAL_FILENAME_INDENT, TEST_FULLNAME, to_filepath);

    free(to_filepath);
}

DEFINE_TEST_FUNC test_to_filename()
{
    char *to_filename = cider_to_filename(STR_DEF_TO_HEAP(TEST_FULLNAME));

    printf("           %*.sTo Filename: \"%s\" -> \"%s\"\n", REAL_FILENAME_INDENT, TEST_FULLNAME, to_filename);

    free(to_filename);
}

DEFINE_TEST_FUNC test_to_extension()
{
    char *to_extension = cider_to_extension(STR_DEF_TO_HEAP(TEST_FULLNAME));

    printf("          %*.sTo Extension: \"%s\" -> \"%s\"\n", REAL_FILENAME_INDENT, TEST_FULLNAME, to_extension);

    free(to_extension);
}

DEFINE_TEST_FUNC test_construct_fullname()
{
    char *construct_fullname = cider_construct_fullname(STR_DEF_TO_HEAP(CIDER_PATH_DELIM_S "home" CIDER_PATH_DELIM_S "dir" CIDER_PATH_DELIM_S), "file.txt");

    printf("    %*.sConstruct Fullname: \"" CIDER_PATH_DELIM_S "home" CIDER_PATH_DELIM_S "dir" CIDER_PATH_DELIM_S "\" + \"file.txt\" -> \"%s\"\n", REAL_FILENAME_INDENT, construct_fullname);

    free(construct_fullname);
}

DEFINE_TEST_FUNC test_forward_slash_delims()
{
    char *forward_slash_delims = cider_forward_slash_delims(STR_DEF_TO_HEAP(TEST_FULLNAME));

    printf("         %*.sFSlash Delims: \"%s\"\n", REAL_FILENAME_INDENT, forward_slash_delims);

    free(forward_slash_delims);
}

DEFINE_TEST_FUNC test_back_slash_delims()
{
    char *back_slash_delims = cider_back_slash_delims(STR_DEF_TO_HEAP(TEST_FULLNAME));

    printf("         %*.sBSlash Delims: \"%s\"\n", REAL_FILENAME_INDENT, back_slash_delims);

    free(back_slash_delims);
}

DEFINE_TEST_FUNC test_canonicalize_real_file()
{
    char *canonicalized_fullname = cider_canonicalize_file(REAL_FILENAME);

    printf("%*.sReal to canon fullname: \"%s\"\n", REAL_FILENAME_INDENT, canonicalized_fullname);

    free(canonicalized_fullname);
}

DEFINE_TEST_FUNC test_canonicalize_fake_file()
{
    char *canonicalized_fullname = cider_canonicalize_file(FAKE_FILENAME);

    printf("%*.sFake to canon fullname: \"%s\"\n", REAL_FILENAME_INDENT, canonicalized_fullname);

    free(canonicalized_fullname);
}

DEFINE_TEST_FUNC test_creation_date_file()
{
    printf("Creation E-seconds of " REAL_FILENAME ": %" PRIu32 "\n", cider_creation_date_file(REAL_FILENAME));
}

DEFINE_TEST_FUNC test_reset_delims()
{
    char *forwards  = cider_reset_delims((char []){ "fslash/test/path/here" }, '/');
    char *backwards = cider_reset_delims((char []){ "bslash\\test\\path\\here" }, '\\');

    printf("          %*.sReset FSlash: \"%s\"\n", REAL_FILENAME_INDENT, forwards);
    printf("          %*.sReset BSlash: \"%s\"\n", REAL_FILENAME_INDENT, backwards);
}

DEFINE_TEST_FUNC test_temp_filepath()
{
    char *temp_filepath = cider_temp_filepath();

    printf("    %*.sTemporary filepath: \"%s\"\n", REAL_FILENAME_INDENT, temp_filepath);

    free(temp_filepath);
}

int main()
{
    // Some functions require a test file
    FILE *test_file = fopen(REAL_FILENAME, "w");
    if (NULL == test_file)
    {
        goto SYSTEM_FAIL;
    }
    else
    {
        fputs("This is a testing file.\n", test_file);
    }

    if (fclose(test_file))
    {
        goto SYSTEM_FAIL;
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

    test_canonicalize_real_file();

    test_canonicalize_fake_file();

    test_creation_date_file();

    test_reset_delims();

    test_temp_filepath();

    return 0;
    SYSTEM_FAIL:

    perror("System fail during test_creation_date_file()");
    return 1;
}
