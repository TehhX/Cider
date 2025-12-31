cmake_minimum_required(VERSION 3.28)
project(cider LANGUAGES C VERSION 0.1.0)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# Provice LIB_TYPE when configuring.
add_library(cider ${LIB_TYPE} src/cider.c)

target_include_directories(cider PRIVATE include)
