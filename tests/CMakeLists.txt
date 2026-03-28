# Will test Cider library. Built as a part of parent folder CMakeLists.txt.

cmake_minimum_required(VERSION 3.28)
project(Cider-Tests LANGUAGES C VERSION 1.0.0)

add_executable(Cider-Tests
    tests.c
)

set(CLOPT_PROJ Cider-Tests)
include("../Compiler_Linker_Opts.cmake")

target_include_directories(Cider-Tests PRIVATE ../include/)
     target_link_libraries(Cider-Tests PRIVATE cider)
