project(src)

set(SRC_SOURCES_AND_HEADERS "" CACHE STRING "src source files")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(core)
add_subdirectory(cpp)

message("src source files: ${SRC_SOURCES_AND_HEADERS}")

add_library(${PROJECT_LIBRARY_NAME} STATIC ${SRC_SOURCES_AND_HEADERS})
add_dependencies(${PROJECT_LIBRARY_NAME} fmtlib_fmt)
add_dependencies(${PROJECT_LIBRARY_NAME} gabime_spdlog)
add_dependencies(${PROJECT_LIBRARY_NAME} davegamble_cjson)
target_link_libraries(${PROJECT_LIBRARY_NAME} PRIVATE dl)

set(PROJECT_SHARED_LIBRARY_NAME ${PROJECT_LIBRARY_NAME}_shared)
add_library(${PROJECT_SHARED_LIBRARY_NAME} SHARED ${SRC_SOURCES_AND_HEADERS})
set_target_properties(${PROJECT_SHARED_LIBRARY_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_LIBRARY_NAME})
add_dependencies(${PROJECT_SHARED_LIBRARY_NAME} fmtlib_fmt)
add_dependencies(${PROJECT_SHARED_LIBRARY_NAME} gabime_spdlog)
add_dependencies(${PROJECT_SHARED_LIBRARY_NAME} davegamble_cjson)
target_link_libraries(${PROJECT_SHARED_LIBRARY_NAME} PRIVATE dl)

install(TARGETS ${PROJECT_LIBRARY_NAME} ${PROJECT_SHARED_LIBRARY_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME})
