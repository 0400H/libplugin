project(registry)

file(GLOB SOURCES_AND_HEADERS "*.cpp" "*.hpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_registry ${SOURCES_AND_HEADERS})

add_dependencies(test_registry doctest_doctest)

target_link_libraries(test_registry PRIVATE ${PROJECT_LIBRARY_NAME})
