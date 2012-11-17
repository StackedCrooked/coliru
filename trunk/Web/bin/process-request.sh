#!/bin/sh
set -x
if [ $# -ne 1 ] ; then
    echo "Usage: $0 request-file" 1>&2
    exit 1
fi

cat request.txt | sed -n 1p | sed 's/\\n/\n/g' > main.user.cpp
cat request.txt | sed -n 2p > compiler-flags.user.txt
g++ -o main.user.binary `cat compiler-flags.user.txt | head -n 1` main.user.cpp >response.txt 2>&1
./main.user.binary >>response.txt 2>&1
