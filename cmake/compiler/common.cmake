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

# generate cmake compiler comands
if(EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

if(ENABLE_VERBOSE_MSG)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

# add_compiler_flags(CMAKE_CXX_FLAGS -v)
add_compiler_flags(CMAKE_CXX_FLAGS -std=c++11)
add_compiler_flags(CMAKE_CXX_FLAGS -fPIC)
add_compiler_flags(CMAKE_CXX_FLAGS -ldl)
add_compiler_flags(CMAKE_CXX_FLAGS -W)
add_compiler_flags(CMAKE_CXX_FLAGS -Wall)
add_compiler_flags(CMAKE_CXX_FLAGS -pthread)
add_compiler_flags(CMAKE_CXX_FLAGS -Werror=return-type)
add_compiler_flags(CMAKE_CXX_FLAGS -Werror=address)
add_compiler_flags(CMAKE_CXX_FLAGS -Werror=sequence-point)
add_compiler_flags(CMAKE_CXX_FLAGS -Wno-unused-variable)
add_compiler_flags(CMAKE_CXX_FLAGS -Wformat)
add_compiler_flags(CMAKE_CXX_FLAGS -Wmissing-declarations)
add_compiler_flags(CMAKE_CXX_FLAGS -Winit-self)
add_compiler_flags(CMAKE_CXX_FLAGS -Wpointer-arith)
add_compiler_flags(CMAKE_CXX_FLAGS -Wshadow)
add_compiler_flags(CMAKE_CXX_FLAGS -fpermissive)
add_compiler_flags(CMAKE_CXX_FLAGS -Wsign-promo)
add_compiler_flags(CMAKE_CXX_FLAGS -fdiagnostics-show-option)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose Release or Debug" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compiler_flags(CMAKE_CXX_FLAGS -O0)
    add_compiler_flags(CMAKE_CXX_FLAGS -g)
    add_compiler_flags(CMAKE_CXX_FLAGS -pg)
    add_compiler_flags(CMAKE_CXX_FLAGS -gdwarf-2) # for old version gcc and gdb. see: http://stackoverflow.com/a/15051109/673852
else()
    add_compiler_flags(CMAKE_CXX_FLAGS -O3)
    add_compiler_flags(CMAKE_CXX_FLAGS -DNDEBUG)
endif()

if(NOISY_WARNINGS)
    add_compiler_flags(CMAKE_CXX_FLAGS -Wcast-align)
    add_compiler_flags(CMAKE_CXX_FLAGS -Wstrict-aliasing=2)
    add_compiler_flags(CMAKE_CXX_FLAGS -Wundef)
    add_compiler_flags(CMAKE_CXX_FLAGS -Wsign-compare)
else()
    add_compiler_flags(CMAKE_CXX_FLAGS -Wno-undef)
    add_compiler_flags(CMAKE_CXX_FLAGS -Wno-narrowing)
    add_compiler_flags(CMAKE_CXX_FLAGS -Wno-unknown-pragmas)
    add_compiler_flags(CMAKE_CXX_FLAGS -Wno-delete-non-virtual-dtor)
    add_compiler_flags(CMAKE_CXX_FLAGS -Wno-comment)
    add_compiler_flags(CMAKE_CXX_FLAGS -Wno-sign-compare)
    add_compiler_flags(CMAKE_CXX_FLAGS -Wno-ignored-qualifiers)
    add_compiler_flags(CMAKE_CXX_FLAGS -Wno-enum-compare)
endif()

if(DISABLE_ALL_WARNINGS)
    add_compiler_flags(CMAKE_CXX_FLAGS -w)
endif()
