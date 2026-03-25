cmake_minimum_required(VERSION 3.28)
project(cider LANGUAGES C VERSION 2.1.0)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)

# Provide LIB_TYPE when configuring or it will be SHARED
if (NOT DEFINED LIB_TYPE)
    set(LIB_TYPE SHARED)
endif ()

add_library(cider ${LIB_TYPE} src/cider.c)

target_include_directories(cider PRIVATE include)

add_subdirectory(tests)

install(TARGETS cider DESTINATION lib)
install(FILES "${CMAKE_SOURCE_DIR}/include/cider.h" DESTINATION include)
