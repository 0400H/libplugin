file(GLOB SOURCES_AND_HEADERS "*.cpp" "*.hpp")

add_library(test_lib SHARED ${SOURCES_AND_HEADERS})
# add_library(test_lib STATIC ${SOURCES_AND_HEADERS})
