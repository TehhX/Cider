cmake_minimum_required(VERSION 3.28)
project(cider LANGUAGES C VERSION 3.0.0)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)

add_library(cider ${LIB_TYPE} src/cider.c)
target_compile_definitions(cider PRIVATE CIDER_EXPORT)

# Provide LIB_TYPE when configuring or it will be SHARED
if (NOT DEFINED LIB_TYPE)
    set(LIB_TYPE "SHARED")
endif ()

# Integral enum LIB_TYPE for definitions
set(LIB_TYPE_SHARED 0)
set(LIB_TYPE_STATIC 1)

target_compile_definitions(cider PRIVATE LIB_TYPE_STATIC=${LIB_TYPE_STATIC})
target_compile_definitions(cider PRIVATE LIB_TYPE_SHARED=${LIB_TYPE_SHARED})

if (LIB_TYPE STREQUAL "SHARED")
    target_compile_definitions(cider PRIVATE LIB_TYPE=${LIB_TYPE_SHARED})
elseif (LIB_TYPE STREQUAL "STATIC")
    target_compile_definitions(cider PRIVATE LIB_TYPE=${LIB_TYPE_STATIC})
else ()
    message(FATAL_ERROR "Provided LIB_TYPE invalid.")
endif ()

set(CLOPT_PROJ cider)
include("Compiler_Linker_Opts.cmake")

target_include_directories(cider PUBLIC "include/")

# Define BUILD_TESTS=1 to test output
if (BUILD_TESTS EQUAL 1)
    add_subdirectory(tests)
endif ()

install(TARGETS cider DESTINATION lib)
install(FILES "${CMAKE_SOURCE_DIR}/include/cider.h" DESTINATION include)
