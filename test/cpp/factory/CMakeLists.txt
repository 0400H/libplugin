set(TEST_SOURCES_AND_HEADERS "" CACHE STRING "src source files")

file(GLOB SOURCES_AND_HEADERS "*.cpp" "*.hpp")

if(NOT "${TEST_SOURCES_AND_HEADERS}" MATCHES "${SOURCES_AND_HEADERS}")
    set(TEST_SOURCES_AND_HEADERS
        "${SOURCES_AND_HEADERS};${TEST_SOURCES_AND_HEADERS}"
        CACHE
        STRING
        "change TEST_SOURCES_AND_HEADERS"
        FORCE)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(hello)
add_subdirectory(world)

add_executable(test_factory ${TEST_SOURCES_AND_HEADERS})

add_dependencies(test_factory doctest_doctest)

target_link_libraries(test_factory PRIVATE plugin)
