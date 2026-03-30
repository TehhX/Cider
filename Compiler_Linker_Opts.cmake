# Set CLOPT_PROJ to project to apply options to

if ("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
    # Compiler/linker options
        if (CMAKE_C_COMPILER_ID STREQUAL GNU)
        target_compile_options(${CLOPT_PROJ} PRIVATE "-fsanitize=address" "-fsanitize=undefined" "-Wall" "-Wextra")
        target_link_options(${CLOPT_PROJ} PRIVATE "-fsanitize=address" "-fsanitize=undefined")
    elseif (CMAKE_C_COMPILER_ID STREQUAL MSVC)
        target_compile_options(${CLOPT_PROJ} PRIVATE "/fsanitize=address" "/fsanitize=undefined")
        target_link_options(${CLOPT_PROJ} PRIVATE "/fsanitize=address" "/fsanitize=undefined")
    endif ()
endif ()
