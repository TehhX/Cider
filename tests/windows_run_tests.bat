@ ECHO OFF

ECHO WARNING: This batch file is untested. If you wish to use/test it, remove the next line.
EXIT /b

ECHO OPTIMIZED:
    gcc -O3 -Wall -Wextra -o Tests.exe ./tests.c -L../build/ -lcider -I../include/
    Tests.exe
    DEL Tests.exe

ECHO
ECHO UNOPTIMIZED:
    gcc -O0 -Wall -Wextra -o Tests.exe ./tests.c -L../build/ -lcider -I../include/
    Tests.exe
    DEL Tests.exe
