file(GLOB SOURCES_AND_HEADERS "*.cpp" "*.hpp")

if(NOT "${EXAMPLES_SOURCES_AND_HEADERS}" MATCHES "${SOURCES_AND_HEADERS}")
    set(EXAMPLES_SOURCES_AND_HEADERS
        "${SOURCES_AND_HEADERS};${EXAMPLES_SOURCES_AND_HEADERS}"
        CACHE
        STRING
        "change EXAMPLES_SOURCES_AND_HEADERS"
        FORCE)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
