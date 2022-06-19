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

add_compiler_flags(CMAKE_CXX_FLAGS -mavx2)
add_compiler_flags(CMAKE_CXX_FLAGS -fopenmp)
add_compiler_flags(CMAKE_CXX_FLAGS -march=native)
add_compiler_flags(CMAKE_CXX_FLAGS -Ofast)
add_compiler_flags(CMAKE_CXX_FLAGS -ffast-math)
add_compiler_flags(CMAKE_CXX_FLAGS -Wall)
add_compiler_flags(CMAKE_CXX_FLAGS -Wno-comment)
add_compiler_flags(CMAKE_CXX_FLAGS -Wno-unused-local-typedefs)
# The -Wno-long-long is required in 64bit systems when including sytem headers.
add_compiler_flags(CMAKE_CXX_FLAGS -Wno-long-long)
