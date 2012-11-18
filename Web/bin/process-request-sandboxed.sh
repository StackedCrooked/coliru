#!/bin/bash
set +x
set -e
ulimit -t 5

if [ `whoami` != "sandboxer" ]; then
    echo "This script must be run by the sandboxer."
    exit 1
fi

if [ $# -ne 1 ] ; then
    echo "Usage $0 SourceFile" 1>&2 && exit 1
fi

OUTPUT=/home/`whoami`/output
mkdir -p ${OUTPUT}
rm -f ${OUTPUT}/*
cp "$1" ${OUTPUT}/main.cpp
cd ${OUTPUT}

if grep -q "^// g++" main.cpp ; then
    cat main.cpp | head -n1 | sed 's,^//[ ],,' > command
else
    echo 'g++ -Wall -o test main.cpp && ./test' > command
fi

cat command
sh command
