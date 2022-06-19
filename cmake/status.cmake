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
# section: prints the statistic of configuration of project.
# --------------------------------------------------------------------

message(STATUS "================================ configuration ==================================")

# message(STATUS "  ${Green}General:${ColourReset}")
message(STATUS "  Project version           : ${BoldWhite}${PROJECT_VERSION}${ColourReset}")
message(STATUS "  Host system processor     : ${BoldWhite}${CMAKE_HOST_SYSTEM_PROCESSOR}${ColourReset}")
message(STATUS "  OS                        : ${BoldWhite}${CMAKE_SYSTEM_NAME}${ColourReset}")
message(STATUS "  C++ compiler              : ${BoldWhite}${CMAKE_C_COMPILER}${ColourReset}")
message(STATUS "  C++ compiler              : ${BoldWhite}${CMAKE_CXX_COMPILER}${ColourReset}")
message(STATUS "  C flags                   : ${CMAKE_C_FLAGS}")
message(STATUS "  CXX flags                 : ${CMAKE_CXX_FLAGS}")
message(STATUS "  Build type                : ${BoldWhite}${CMAKE_BUILD_TYPE}${ColourReset}")
message(STATUS "  Build library type        : ${BoldWhite}${BUILD_LIB_TYPE}${ColourReset}")
message(STATUS "  Build processor arch      : ${BoldWhite}${Build_PROCESSOR_ARCH}${ColourReset}")
message(STATUS "  Enable verbose message    : ${ENABLE_VERBOSE_MSG}")
message(STATUS "  Disable all warnings      : ${DISABLE_ALL_WARNINGS}")
message(STATUS "  Export compile command    : ${EXPORT_COMPILE_COMMANDS}")

if(USE_OPENMP)
    message(STATUS "  USE_OPENMP                : ${USE_OPENMP}")
endif()

message(STATUS "  Build with test           : ${BUILD_TEST}")
message(STATUS "  Build with benchmark      : ${BUILD_BENCHMARK}")
message(STATUS "  Build with examples       : ${BUILD_EXAMPLES}")

message(STATUS "  Configuation path         : ${PROJECT_BINARY_DIR}/project_config.h")
message(STATUS "================================ End ==================================")