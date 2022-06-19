function(extract_version)
    execute_process(COMMAND
                    cat "VERSION"
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                    OUTPUT_VARIABLE PROJECT_VERSION
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(PROJECT_VERSION ${PROJECT_VERSION})
    add_compile_definitions(MG_ENABLE_OPENSSL=${PROJECT_VERSION})
    # add_definitions(-DPROJECT_VERSION)
endfunction()

macro(append_var_value var value)
    set(${var} "${${var}} ${value}")
endmacro()

macro(add_compiler_flags compiler flag)
    append_var_value(${compiler} ${flag})
endmacro()

function(add_c_flags arg)
    message(STATUS "ARGC: ${ARGC}")
    message(STATUS "ARGV: ${ARGV}")
    message(STATUS "ARGN: ${ARGN}")
    list(LENGTH ARGV argv_len)
    set(i 0)
    while(i LESS ${argv_len})
        list(GET ARGV ${i} argv_value)
        math(EXPR i "${i} + 1")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${argv_value}" PARENT_SCOPE)
    endwhile()
endfunction ()

function(add_cxx_flags arg)
    # message(STATUS "ARGC: ${ARGC}")
    # message(STATUS "ARGV: ${ARGV}")
    # message(STATUS "ARGN: ${ARGN}")
    list(LENGTH ARGV argv_len)
    set(i 0)
    while(i LESS ${argv_len})
        list(GET ARGV ${i} argv_value)
        math(EXPR i "${i} + 1")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${argv_value}" PARENT_SCOPE)
    endwhile()
endfunction ()
