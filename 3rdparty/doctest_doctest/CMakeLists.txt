cmake_minimum_required(VERSION 3.17)

set(DOCTEST_ROOT ${CMAKE_BINARY_DIR}/3rdparty/doctest_doctest)
set(DOCTEST_SOURCE ${DOCTEST_ROOT}/src/doctest_doctest)
set(DOCTEST_INSTALL ${DOCTEST_ROOT}/install)
set(DOCTEST_INCLUDE ${DOCTEST_INSTALL}/include)
set(DOCTEST_LIBRARY ${DOCTEST_INSTALL}/lib)
set(CMAKE_ARGS -DCMAKE_VERBOSE_MAKEFILE=ON
               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_INSTALL_PREFIX=${DOCTEST_INSTALL}
               -DDOCTEST_WITH_TESTS=OFF
               -DDOCTEST_NO_INSTALL=OFF .)

include(ExternalProject)
ExternalProject_Add(doctest_doctest
    PREFIX            ${DOCTEST_ROOT}
    GIT_REPOSITORY    https://github.com/doctest/doctest.git
    GIT_TAG           v2.4.8
    BUILD_ALWAYS      OFF
    LOG_DOWNLOAD      OFF
    LOG_BUILD         OFF
    LOG_INSTALL       OFF
    # UPDATE_COMMAND    "" # setup patch
    CMAKE_ARGS        ${CMAKE_ARGS}
    # CONFIGURE_COMMAND cd ${DOCTEST_SOURCE} && cmake ${CMAKE_ARGS}
    # BUILD_COMMAND     cd ${DOCTEST_SOURCE} && $(MAKE) -j ${PARALLEL_JOBS}
    # INSTALL_COMMAND   cd ${DOCTEST_SOURCE} && $(MAKE) install
    # TEST_COMMAND      ""
    # SOURCE_DIR        ""
    # BINARY_DIR        ""
)

ExternalProject_Get_Property(doctest_doctest)
include_directories(${DOCTEST_INCLUDE})

# include(FetchContent)
# FetchContent_Declare(doctest
#     GIT_REPOSITORY https://github.com/doctest/doctest.git
#     GIT_TAG v2.4.8)

# 建议使用压缩包的方式依赖，下载速度更快
# FetchContent_Declare(doctest
#    URL https://github.com/doctest/doctest/archive/refs/tags/v2.4.8.tar.gz)

# FetchContent_MakeAvailable(doctest)

# target_link_libraries(doctest PRIVATE doctest::doctest)
