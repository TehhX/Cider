cmake_minimum_required(VERSION 3.28)
project(cider LANGUAGES C VERSION 3.0.0)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)

# Provide LIB_TYPE when configuring or it will be SHARED
if (NOT DEFINED LIB_TYPE)
    set(LIB_TYPE SHARED)
endif ()

add_library(cider ${LIB_TYPE} src/cider.c)
target_compile_definitions(cider PRIVATE CIDER_EXPORT)

set(CLOPT_PROJ cider)
include("Compiler_Linker_Opts.cmake")

target_include_directories(cider PRIVATE include)

# Define BUILD_TESTS=1 to test output
if (DEFINED BUILD_TESTS)
    add_subdirectory(tests)
endif ()

install(TARGETS cider DESTINATION lib)
install(FILES "${CMAKE_SOURCE_DIR}/include/cider.h" DESTINATION include)
