#!/bin/bash
set -e

shopt -s expand_aliases
shopt expand_aliases

export LOG_NAME=$(date '+%Y%m%d.%H%M%S').$(hostname)
export LIBPLUGIN_LOG_LEVEL=info

echo -e 'using LOG_NAME='${LOG_NAME}
echo -e 'using LOG_LEVEL='${LIBPLUGIN_LOG_LEVEL}

LOG_DIR=`pwd -P`/logs
mkdir -p ${LOG_DIR}

cd build/test/cpp/library && ./test_library 2>&1 | tee -a ${LOG_DIR}/${LOG_NAME}.log && cd -
cd build/test/cpp/factory && ./test_factory 2>&1 | tee -a ${LOG_DIR}/${LOG_NAME}.log && cd -
cd build/test/cpp/registry && ./test_registry 2>&1 | tee -a ${LOG_DIR}/${LOG_NAME}.log && cd -

cd build/examples/cpp/hello_world && ./hello_world 2>&1 | tee -a ${LOG_DIR}/${LOG_NAME}.log && cd -
