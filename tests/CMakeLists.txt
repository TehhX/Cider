# Will test Cider library. Built as a part of parent folder CMakeLists.txt.

cmake_minimum_required(VERSION 3.28)
project(Cider-Tests LANGUAGES C VERSION 1.0.0)

add_executable(Cider-Tests
    tests.c
)

# Sanitize options
if (CMAKE_C_COMPILER_ID STREQUAL GNU)
    target_compile_options(Cider-Tests PRIVATE "-fsanitize=address" "-fsanitize=undefined")
       target_link_options(Cider-Tests PRIVATE "-fsanitize=address" "-fsanitize=undefined")
elseif (CMAKE_C_COMPILER_ID STREQUAL MSVC)
    target_compile_options(Cider-Tests PRIVATE "/fsanitize=address" "/fsanitize=undefined")
       target_link_options(Cider-Tests PRIVATE "/fsanitize=address" "/fsanitize=undefined")
endif ()

target_include_directories(Cider-Tests PRIVATE ../include/)
     target_link_libraries(Cider-Tests PRIVATE cider)
