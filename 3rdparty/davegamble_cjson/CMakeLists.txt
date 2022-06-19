cmake_minimum_required(VERSION 3.17)

project(davegamble_cjson C CXX)

set(CJSON_ROOT ${CMAKE_BINARY_DIR}/3rdparty/davegamble_cjson)
set(CJSON_SOURCE ${CJSON_ROOT}/src/davegamble_cjson)
set(CJSON_INSTALL ${CJSON_ROOT}/install)
set(CJSON_INCLUDE ${CJSON_INSTALL}/include)
set(CJSON_LIBRARY ${CJSON_INSTALL}/lib)
set(CMAKE_ARGS -DCMAKE_VERBOSE_MAKEFILE=ON
               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_INSTALL_PREFIX=${CJSON_INSTALL}
               -DBUILD_SHARED_AND_STATIC_LIBS=ON
               -DBUILD_SHARED_LIBS=OFF
               -DENABLE_CJSON_TEST=OFF .)

include(ExternalProject)
ExternalProject_Add(davegamble_cjson
    PREFIX            ${CJSON_ROOT}
    GIT_REPOSITORY    https://github.com/DaveGamble/cJSON.git
    GIT_TAG           v1.7.15
    BUILD_ALWAYS      OFF
    LOG_DOWNLOAD      OFF
    LOG_BUILD         OFF
    LOG_INSTALL       OFF
    # UPDATE_COMMAND    "" # setup patch
    CMAKE_ARGS        ${CMAKE_ARGS}
    # CONFIGURE_COMMAND cd ${CJSON_SOURCE} && cmake ${CMAKE_ARGS}
    # BUILD_COMMAND     cd ${CJSON_SOURCE} && $(MAKE) -j ${PARALLEL_JOBS}
    # INSTALL_COMMAND   cd ${CJSON_SOURCE} && $(MAKE) install
    # TEST_COMMAND      ""
    # SOURCE_DIR        ""
    # BINARY_DIR        ""
)

ExternalProject_Get_Property(cjson)
include_directories(${CJSON_INCLUDE})
