#! /bin/bash

echo OPTIMIZED:
    gcc -O3 -Wall -Wextra -o Tests ./tests.c -L../build/ -lcider -I../include/
    ./Tests
    rm Tests

echo
echo UNOPTIMIZED:
    gcc -O0 -Wall -Wextra -o Tests ./tests.c -L../build/ -lcider -I../include/
    ./Tests
    rm Tests
