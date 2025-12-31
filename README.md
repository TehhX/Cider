# Cider
A small library containing some path and directory manipulation tools written in C17.

## Tests
Contains any test-related files to verify if Cider is functioning properly.

## Library Type
Using a shared library type will not allow inlining to occur. Configure CMake with -DLIB_TYPE=\<type> where \<type> is SHARED or STATIC to change type. Don't provide LIB_TYPE to use default if you don't care.
