#! /bin/bash

gcc -O3 -Wall -Wextra -I ../include -o Tests ../src/cider.c ./tests.c
./Tests
rm Tests
