#!/bin/bash
ulimit -u 20
ulimit -t TIMEOUT
export LD_LIBRARY_PATH="/usr/local/lib:${LD_LIBRARY_PATH}"
cd ${1}
./cmd.sh
