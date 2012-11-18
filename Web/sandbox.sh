#!/bin/bash
#set -x
set -e
ulimit -t 1

if [ $# -ne 1 ] ; then
    echo "Usage $0 SourceFile" 1>&2 && exit 1
fi

rm -f /tmp/main.cpp
rm -f /tmp/test


cat $1 > /tmp/main.cpp
cd /tmp

# Default command
echo ' -Wall -o test main.cpp && ./test' > ./cmd

# Can be overriden
if grep -q "^// c.." main.cpp ; then
    cat main.cpp | head -n1 | sed 's,^//[ ]c++,,' > ./cmd
fi

# Run the command
CMD="c++ `cat /tmp/cmd`"
echo ${CMD}
$CMD

RUN="./test"
echo "${RUN}"
${RUN}
