project(library)

file(GLOB SOURCES_AND_HEADERS "*.cpp" "*.hpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(test_lib)

add_executable(test_library ${SOURCES_AND_HEADERS})

add_dependencies(test_library doctest_doctest)

target_link_libraries(test_library PRIVATE ${PROJECT_LIBRARY_NAME})
