cmake_minimum_required(VERSION 3.28)
project(cider LANGUAGES C)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_library(cider SHARED src/cider.c)

target_include_directories(cider PRIVATE include)
