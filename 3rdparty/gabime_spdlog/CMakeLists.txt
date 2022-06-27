cmake_minimum_required(VERSION 3.17)

set(SPDLOG_ROOT ${CMAKE_BINARY_DIR}/3rdparty/gabime_spdlog)
set(SPDLOG_SOURCE ${SPDLOG_ROOT}/src/gabime_spdlog)
set(SPDLOG_INSTALL_PREFIX ${SPDLOG_ROOT}/install)
set(SPDLOG_INCLUDE ${SPDLOG_INSTALL_PREFIX}/include)
set(SPDLOG_LIBRARY ${SPDLOG_INSTALL_PREFIX}/lib)
set(CMAKE_ARGS -DCMAKE_VERBOSE_MAKEFILE=ON
               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_INSTALL_PREFIX=${SPDLOG_INSTALL_PREFIX}
               -DSPDLOG_BUILD_EXAMPLE=OFF
               -DSPDLOG_INSTALL=ON .)

include(ExternalProject)
ExternalProject_Add(gabime_spdlog
    PREFIX            ${SPDLOG_ROOT}
    GIT_REPOSITORY    https://github.com/gabime/spdlog.git
    GIT_TAG           v1.10.0
    BUILD_ALWAYS      OFF
    LOG_DOWNLOAD      OFF
    LOG_BUILD         OFF
    LOG_INSTALL       OFF
    # UPDATE_COMMAND    "" # setup patch
    CMAKE_ARGS        ${CMAKE_ARGS}
    # CONFIGURE_COMMAND cd ${SPDLOG_SOURCE} && cmake ${CMAKE_ARGS}
    # BUILD_COMMAND     cd ${SPDLOG_SOURCE} && $(MAKE) -j ${PARALLEL_JOBS}
    # INSTALL_COMMAND   cd ${SPDLOG_SOURCE} && $(MAKE) install
    # TEST_COMMAND      ""
    # SOURCE_DIR        ""
    # BINARY_DIR        ""
)

ExternalProject_Get_Property(gabime_spdlog)
include_directories(${SPDLOG_INCLUDE})
link_directories(${SPDLOG_LIBRARY})

# include(FetchContent)
# FetchContent_Declare(spdlog
#     GIT_REPOSITORY https://github.com/gabime/spdlog.git
#     GIT_TAG v1.10.0)

# 建议使用压缩包的方式依赖，下载速度更快
# FetchContent_Declare(spdlog
#    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz)

# FetchContent_MakeAvailable(spdlog)

# target_link_libraries(spdlog PRIVATE spdlog::spdlog)
