# Will test Cider library. Built as a part of parent folder CMakeLists.txt.

cmake_minimum_required(VERSION 3.28)
project(Cider-Tests LANGUAGES C)

add_executable(Cider-Tests
    tests.c
)

include("${CMAKE_SOURCE_DIR}/Compiler_Linker_Opts.cmake")

target_link_libraries(Cider-Tests PRIVATE cider)
