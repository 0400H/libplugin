# Copyright (c) 2018 PROJECTAUTHOR Authors, Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set(MIN_CMAKE_V 3.19.2)
cmake_minimum_required(VERSION ${MIN_CMAKE_V} FATAL_ERROR)

set(PROJECT_NAME "libplugin")
project(${PROJECT_NAME} C CXX)

# --------------------------------------------------------------------
# section: cmake variables
# --------------------------------------------------------------------

# set project version
file(STRINGS "VERSION" FILE_VERSION)
set(PROJECT_VERSION ${FILE_VERSION})
string(REPLACE "." ";" VERSION_LIST ${PROJECT_VERSION})
list(GET VERSION_LIST 0 VERSION_MAJOR)
list(GET VERSION_LIST 1 VERSION_MINOR)
list(GET VERSION_LIST 2 VERSION_PATCH)

# set project library name
set(PROJECT_LIBRARY_NAME "plugin")

# set modules dir
set(PROJECT_ROOT ${PROJECT_SOURCE_DIR})
set(PROJECT_CMAKE ${PROJECT_ROOT}/cmake)
set(PROJECT_INCLUDE ${PROJECT_ROOT}/include)
set(PROJECT_SRC ${PROJECT_ROOT}/src)
set(PROJECT_TEST ${PROJECT_ROOT}/test)
set(PROJECT_EXAMPLES ${PROJECT_ROOT}/examples)
set(PROJECT_3RDPARTY ${PROJECT_ROOT}/3rdparty)

# --------------------------------------------------------------------
# section: cmake options
# --------------------------------------------------------------------

# set compiler options
option(ENABLE_VERBOSE_MSG "Enable verbose=1 : compile msg during make." OFF)
option(DISABLE_ALL_WARNINGS "Disable all the warning msg during compile." ON)
option(EXPORT_COMPILE_COMMANDS "Export compile command to json." ON)
option(Build_PROCESSOR_ARCH "Export compile command to json." "x86_64")
option(BUILD_LIB_TYPE "Build project lib type." "static")

# set internal components
option(BUILD_DOC "Build project doc components." OFF)
option(BUILD_TEST "Build project test components." ON)
option(BUILD_EXAMPLES "Build project examples components." ON)

# --------------------------------------------------------------------
# section: cmake configuration and show status
# --------------------------------------------------------------------

include(${PROJECT_CMAKE}/colors.cmake)
include(${PROJECT_CMAKE}/utils.cmake)
include(${PROJECT_CMAKE}/compiler/compiler.cmake)
include(${PROJECT_CMAKE}/status.cmake)

# --------------------------------------------------------------------
# section: find and include 3rdparty modules
# --------------------------------------------------------------------

include(${PROJECT_3RDPARTY}/fmtlib_fmt/CMakeLists.txt)
include(${PROJECT_3RDPARTY}/gabime_spdlog/CMakeLists.txt)
# include(${PROJECT_3RDPARTY}/davegamble_cjson/CMakeLists.txt)

# --------------------------------------------------------------------
# section: add header dirs to search path
# --------------------------------------------------------------------

include_directories(${PROJECT_INCLUDE})

# --------------------------------------------------------------------
# section: add source dirs to build path
# --------------------------------------------------------------------

add_subdirectory(${PROJECT_INCLUDE})
add_subdirectory(${PROJECT_SRC})

if(BUILD_TEST)
    add_subdirectory(${PROJECT_TEST})
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(${PROJECT_EXAMPLES})
endif()

if(BUILD_DOC)
    add_subdirectory(${PROJECT_DOC})
endif()
