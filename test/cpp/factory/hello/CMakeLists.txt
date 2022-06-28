file(GLOB SOURCES_AND_HEADERS "*.cpp" "*.hpp")

add_library(testhello SHARED ${SOURCES_AND_HEADERS})
