project(src)

set(SRC_SOURCES_AND_HEADERS "" CACHE STRING "src source files")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(core)
add_subdirectory(cpp)

message("src source files: ${SRC_SOURCES_AND_HEADERS}")
# add_library(plugin SHARED STATIC ${SRC_SOURCES_AND_HEADERS})
add_library(plugin STATIC ${SRC_SOURCES_AND_HEADERS})

add_dependencies(plugin fmtlib_fmt)
add_dependencies(plugin gabime_spdlog)
add_dependencies(plugin davegamble_cjson)

target_link_libraries(plugin PRIVATE dl)

install(TARGETS plugin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME})
