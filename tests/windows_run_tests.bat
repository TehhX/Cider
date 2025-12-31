@ echo off

gcc -O3 -Wall -Wextra -I ../include -o Tests.exe ../src/cider.c ./tests.c
Tests.exe
del Tests.exe
