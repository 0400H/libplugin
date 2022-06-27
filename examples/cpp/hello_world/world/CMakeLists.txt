file(GLOB SOURCES_AND_HEADERS "*.cpp" "*.hpp")

add_library(world SHARED ${SOURCES_AND_HEADERS})
