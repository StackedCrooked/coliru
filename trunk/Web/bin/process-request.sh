#!/bin/sh
set -x
if [ $# -ne 1 ] ; then
    echo "Usage: $0 request-file" 1>&2
    exit 1
fi

cat request.txt | head -n 1 | sed 's/\\n/\n/g' > main.user.cpp
cat request.txt | head -n 2 | tail -n 1 > compiler-flags.user.txt
g++ -o main.user.binary `cat compiler-flags.user.txt | head -n 1` main.user.cpp >response.txt 2>&1
./main.user.binary >>response.txt 2>&1
