file(GLOB SOURCES_AND_HEADERS "*.cpp" "*.hpp")

# set(SOURCES_AND_HEADERS
#     ${PROJECT_SRC}/core/library/library_manager.cpp
#     ${PROJECT_SRC}/core/library/library_sal.hpp
# )

set(GLOBAL_SOURCES_AND_HEADERS
    "${GLOBAL_SOURCES_AND_HEADERS};${SOURCES_AND_HEADERS}"
    CACHE
    STRING
    "change GLOBAL_SOURCES_AND_HEADERS"
    FORCE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# message("SOURCES_AND_HEADERS: ${SOURCES_AND_HEADERS}")
# message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
# message("GLOBAL_SOURCES_AND_HEADERS: ${GLOBAL_SOURCES_AND_HEADERS}")
