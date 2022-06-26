project(container)

file(GLOB SOURCES_AND_HEADERS "*.cpp" "*.hpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_container ${SOURCES_AND_HEADERS})

add_dependencies(test_library fmtlib_fmt)
add_dependencies(test_library gabime_spdlog)
add_dependencies(test_library doctest_doctest)

target_link_libraries(test_container PRIVATE plugin)
