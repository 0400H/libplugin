#!/bin/bash
set -e

clear && clear

parallel_jobs=$[`nproc`-1]

BUILD_DIR=`pwd -P`/build
mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR}

if [ ! -n "${INSTALL_PREFIX}" ]; then
    INSTALL_PREFIX=${BUILD_DIR}/install
fi

cmake -DCMAKE_CXX_STANDARD=11 \
      -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
      -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
      ..

make -j ${parallel_jobs}
make install

if [ $? -eq 0 ]; then
    echo "build success!"
else
    echo "build failed!"
    exit -1
fi

cd -
