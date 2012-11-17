#!/bin/sh
set -e
if [ "$(whoami)" != "sandboxer" ]; then
    echo "This script must be run by the sandboxer."
    exit 1
fi

rm output/*
cd output
cat ../request.txt > main.cpp
cat main.cpp | head -n1 > options
if grep -q "^// g++" options ; then
    cat ${OPTIONS} | sed 's,^// g++,,' > options
else
    echo "-Wall -o test main.cpp" > options
fi
BUILD_COMMAND="g++ `cat options | head -n 1` -o test main.cpp"
set -x
$BUILD_COMMAND
./test
