include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(hello_world)

target_link_libraries(hello_world PRIVATE ${PROJECT_LIBRARY_NAME})