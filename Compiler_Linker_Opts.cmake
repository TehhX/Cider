if ("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
        # Compiler/linker options
        if (CMAKE_C_COMPILER_ID STREQUAL GNU)
        target_compile_options(${PROJECT_NAME} PRIVATE "-fsanitize=address" "-fsanitize=undefined" "-Wall" "-Wextra")
        target_link_options(${PROJECT_NAME} PRIVATE "-fsanitize=address" "-fsanitize=undefined")
    elseif (CMAKE_C_COMPILER_ID STREQUAL MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE "/fsanitize=address" "/W4")
    endif ()
endif ()
