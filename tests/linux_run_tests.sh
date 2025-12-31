#! /bin/bash

echo OPTIMIZED:
    gcc -fsanitize=address -g -O3 -Wall -Wextra -o Tests_IGN ./tests.c -L../build/ -lcider -I../include/
    ./Tests_IGN

echo
echo UNOPTIMIZED:
    gcc -fsanitize=address -g -O0 -Wall -Wextra -o Tests_IGN ./tests.c -L../build/ -lcider -I../include/
    ./Tests_IGN
