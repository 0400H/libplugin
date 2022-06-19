project(davegamble_cjson C CXX)

file(GLOB SOURCES_AND_HEADERS "*.cpp" "include/*.h")

add_library(test_lib SHARED ${SOURCES_AND_HEADERS})
# add_library(test_lib STATIC ${SOURCES_AND_HEADERS})
