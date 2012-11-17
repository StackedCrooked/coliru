#!/bin/sh
set -e
if [ "$(whoami)" != "sandboxer" ]; then
    echo "This script must be run by the sandboxer."
    exit 1
fi

rm -f output/*
cd output
cat ../request.txt > main.cpp
cat main.cpp | head -n1 > options
if grep -q "^// g++ -o test" options ; then
    cat ${OPTIONS} | sed 's,^// g++,,' > options
else
    echo "-Wall main.cpp" > options
fi
BUILD_COMMAND="g++ -o test `cat options | head -n 1`"
$BUILD_COMMAND
./test
