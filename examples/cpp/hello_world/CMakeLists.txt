file(GLOB SOURCES_AND_HEADERS "*.cpp" "*.hpp")

add_executable(hello_world main.cpp ${SOURCES_AND_HEADERS})

target_include_directories(hello_world
                           PUBLIC
                           ${PROJECT_SOURCE_DIR}/include)

add_dependencies(hello_world fmtlib_fmt)
add_dependencies(hello_world gabime_spdlog)
add_dependencies(hello_world davegamble_cjson)

# target_link_libraries(hello_world PRIVATE spdlog::spdlog)
# target_link_libraries(hello_world PRIVATE fmt::fmt)
