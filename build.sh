#!/bin/bash
set -e

parallel_jobs=$[`nproc`-1]

mkdir -p build && cd build

clear && clear

if [ -z INSTALL_PREFIX ]; then
    INSTALL_PREFIX=`pwd -P`
fi

cmake -DCMAKE_CXX_STANDARD=11 \
      -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
      -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
      ..

make -j ${parallel_jobs}
# make doc -j ${parallel_jobs}

if [ $? -eq 0 ]; then
    echo "build success!"
else
    echo "build failed!"
    exit -1
fi

cd -
