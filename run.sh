#!/bin/bash
set -e

shopt -s expand_aliases
shopt expand_aliases

export CORE_NUM=$(lscpu | grep 'On-line CPU(s) list' | awk '{print $4}' | cut -d '-' -f2)
export CORE_RANGE='0-'$[$CORE_NUM - 1]

export OMP_NUM_THREADS=${CORE_NUM}
export MKL_NUM_THREADS=${CORE_NUM}
export MKL_VERBOSE=0
export MKLDNN_VERBOSE=0

unset KMP_AFFINITY
export KMP_AFFINITY='granularity=fine,compact,0,0' # when HT if OFF
# export KMP_AFFINITY='granularity=fine,compact,1,0' # when HT is ON
export KMP_BLOCKTIME=20

export no_proxy='localhost, 127.0.0.1'
export PYTHONPATH=${PYTHONPATH}:$(pwd -P)
export FILE_NAME=$(date '+%Y%m%d.%H%M%S').$(hostname)

echo -e 'using CORE_RANGE='${CORE_RANGE}
echo -e 'using FILE_NAME='${FILE_NAME}
echo -e 'using PYTHONPATH='${PYTHONPATH}

# alias BIND_CPU_MEM="taskset -c ${CORE_RANGE} numactl -l"
alias BIND_CPU_MEM="taskset -c ${CORE_RANGE}"

LOG_DIR=`pwd -P`/logs
mkdir -p ${LOG_DIR}

cd build/test/cpp/library && BIND_CPU_MEM ./test_library -s 2>&1 | tee -a ${LOG_DIR}/${FILE_NAME}.log && cd -

cd build/test/cpp/registry && BIND_CPU_MEM ./test_registry -s 2>&1 | tee -a ${LOG_DIR}/${FILE_NAME}.log && cd -

cd build/examples/cpp/hello_world && BIND_CPU_MEM ./hello_world 2>&1 | tee -a ${LOG_DIR}/${FILE_NAME}.log && cd -
