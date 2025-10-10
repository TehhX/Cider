cmake_minimum_required(VERSION 3.28)
project(Cider LANGUAGES C)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

if ("${LIB_TYPE}" STREQUAL "")
    message(FATAL_ERROR "Specify LIB_TYPE as SHARED or STATIC.")
endif()

add_library(Cider ${LIB_TYPE} src/cider.c)

target_include_directories(Cider PRIVATE include)
