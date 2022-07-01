cmake_minimum_required(VERSION 3.17)

set(PACKAGE_NAME davegamble_cjson)
set(ROOT_PATH ${CMAKE_BINARY_DIR}/3rdparty/${ROOT_NAME})
set(SOURCE_PATH ${ROOT_PATH}/src/${ROOT_NAME})
set(INSTALL_PATH ${ROOT_PATH}/install)
set(INCLUDE_PATH ${INSTALL_PATH}/include)
set(LIBRARTY_PATH ${INSTALL_PATH}/lib)
set(CMAKE_ARGS -DCMAKE_VERBOSE_MAKEFILE=ON
               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_INSTALL_PREFIX=${INSTALL_PATH}
               -DBUILD_SHARED_AND_STATIC_LIBS=ON
               -DBUILD_SHARED_LIBS=OFF
               -DENABLE_CJSON_TEST=OFF .)

if(EXISTS ${INSTALL_PATH})
    set(UPDATE_DISCONNECTED 1)
else()
    set(UPDATE_DISCONNECTED 0)
endif()

include(ExternalProject)
ExternalProject_Add(${PACKAGE_NAME}
    PREFIX                 ${ROOT_PATH}
    GIT_REPOSITORY         https://github.com/DaveGamble/cJSON.git
    GIT_TAG                v1.7.15
    BUILD_ALWAYS           OFF
    LOG_DOWNLOAD           OFF
    LOG_BUILD              OFF
    LOG_INSTALL            OFF
    UPDATE_DISCONNECTED    ${UPDATE_DISCONNECTED}
    CMAKE_ARGS             ${CMAKE_ARGS}
)
ExternalProject_Get_Property(${PACKAGE_NAME})

include_directories(${INCLUDE_PATH})
link_directories(${LIBRARTY_PATH})
