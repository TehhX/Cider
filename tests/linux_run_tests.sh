#! /bin/bash

# Currently only supports gcc.

# which returns != 0 if not found, == 0 if found.
which gcc &> /dev/null
if [ $? == 0 ]
then
    # Check -O3
    echo -e '\n---\nOPTIMIZED:'
    gcc -fsanitize=address -g -O3 -Wall -Wextra -o Tests_IGN.elf ./tests.c -L../build/ -lcider -I../include/
    ./Tests_IGN.elf

    # Check -O0
    echo -e '---\nUNOPTIMIZED:'
    gcc -fsanitize=address -g -O0 -Wall -Wextra -o Tests_IGN.elf ./tests.c -L../build/ -lcider -I../include/
    ./Tests_IGN.elf

    rm Tests_IGN.elf

    exit 0
fi

# Add other compilers here in the same form.

# Didn't exit at completion of any other compiler:
echo "No compilers found. Check tests/linux_run_tests.sh for supported compilers."
exit 1
