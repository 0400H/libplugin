project(test)

include(${PROJECT_3RDPARTY}/doctest_doctest/CMakeLists.txt)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(cpp)
