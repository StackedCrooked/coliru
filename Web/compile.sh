#!/bin/bash
ulimit -u 20
ulimit -t ${COLIRU_TIMEOUT}
cd /tmp
export LD_LIBRARY_PATH="/usr/local/lib:${LD_LIBRARY_PATH}"
./cmd.sh
