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

# --------------------------------------------------------------------
# section: set the compiler and linker options
# --------------------------------------------------------------------

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "Set CCompiler Flags" FORCE)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "Set C++ Compiler Flags" FORCE)

include(${PROJECT_CMAKE}/compiler/common.cmake)

if(Build_PROCESSOR_ARCH STREQUAL "x86_64")
    include(${PROJECT_CMAKE}/compiler/x86_64.cmake)
endif()
