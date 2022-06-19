project(src)

set(GLOBAL_SOURCES_AND_HEADERS "" CACHE STRING "source files")

add_subdirectory(core)
add_subdirectory(cpp)

message("files: ${GLOBAL_SOURCES_AND_HEADERS}")
add_library(plugin SHARED STATIC ${GLOBAL_SOURCES_AND_HEADERS})
target_link_libraries(plugin PRIVATE dl)
