#!/bin/bash
set -x
cd /home/francis/programming/projects/coliru/Web
if [ "$(whoami)" != "sandboxer" ]; then
    echo "This script must be run by the sandboxer."
    exit 1
fi

rm -rf ./output/*
cd output

cat ../request.txt > ./main.cpp
TMPCMD=tmpcmd.txt
cat ../request.txt | head -n1 > $TMPCMD
if grep -q "^// g++" $TMPCMD ; then
    cat ${TMPCMD} | sed 's,^// g++,,' > compiler-flags.txt
else
    echo "-Wall -o test main.cpp" > compiler-flags.txt
fi

ps -ef
BUILD_COMMAND="g++ `cat compiler-flags.txt | head -n 1`"
$BUILD_COMMAND && ./test
