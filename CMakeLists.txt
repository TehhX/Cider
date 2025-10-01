cmake_minimum_required(VERSION 3.28)
project(Cider LANGUAGES C)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_library(Cider STATIC src/cider.c)
