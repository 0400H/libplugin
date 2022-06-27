set(EXAMPLES_SOURCES_AND_HEADERS "" CACHE STRING "src source files")

file(GLOB SOURCES_AND_HEADERS "*.cpp" "*.hpp")

if(NOT "${EXAMPLES_SOURCES_AND_HEADERS}" MATCHES "${SOURCES_AND_HEADERS}")
    set(EXAMPLES_SOURCES_AND_HEADERS
        "${SOURCES_AND_HEADERS};${EXAMPLES_SOURCES_AND_HEADERS}"
        CACHE
        STRING
        "change EXAMPLES_SOURCES_AND_HEADERS"
        FORCE)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(hello)
add_subdirectory(world)
add_subdirectory(my_plugin)

add_executable(hello_world ${EXAMPLES_SOURCES_AND_HEADERS})

target_link_libraries(hello_world PRIVATE plugin)
