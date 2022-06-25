cmake_minimum_required(VERSION 3.17)

set(FMT_ROOT ${CMAKE_BINARY_DIR}/3rdparty/fmtlib_fmt)
set(FMT_SOURCE ${FMT_ROOT}/src/fmtlib_fmt)
set(FMT_INSTALL ${FMT_ROOT}/install)
set(FMT_INCLUDE ${FMT_INSTALL}/include)
set(FMT_LIBRARY ${FMT_INSTALL}/lib)
set(CMAKE_ARGS -DCMAKE_VERBOSE_MAKEFILE=ON
               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_INSTALL_PREFIX=${FMT_INSTALL}
               -DFMT_DOC=OFF
               -DFMT_TEST=OFF
               -DFMT_INSTALL=ON .)

include(ExternalProject)
ExternalProject_Add(fmtlib_fmt
    PREFIX            ${FMT_ROOT}
    GIT_REPOSITORY    https://github.com/fmtlib/fmt.git
    GIT_TAG           8.1.1
    BUILD_ALWAYS      OFF
    LOG_DOWNLOAD      OFF
    LOG_BUILD         OFF
    LOG_INSTALL       OFF
    # UPDATE_COMMAND    "" # setup patch
    CMAKE_ARGS        ${CMAKE_ARGS}
    # CONFIGURE_COMMAND cd ${FMT_SOURCE} && cmake ${CMAKE_ARGS}
    # BUILD_COMMAND     cd ${FMT_SOURCE} && $(MAKE) -j ${PARALLEL_JOBS}
    # INSTALL_COMMAND   cd ${FMT_SOURCE} && $(MAKE) install
    # TEST_COMMAND      ""
    # SOURCE_DIR        ""
    # BINARY_DIR        ""
)

ExternalProject_Get_Property(fmtlib_fmt)
include_directories(${FMT_INCLUDE})

# include(FetchContent)
# FetchContent_Declare(fmt
#     GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#     GIT_TAG 8.1.1)

# 建议使用压缩包的方式依赖，下载速度更快
# FetchContent_Declare(fmt
#    URL https://github.com/fmtlib/fmt/archive/refs/tags/8.1.1.tar.gz)

# FetchContent_MakeAvailable(fmt)

# target_link_libraries(fmt PRIVATE fmt::fmt)
