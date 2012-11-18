#!/bin/bash
set +x
set -e
ulimit -t 5

if [ $# -ne 1 ] ; then
    echo "Usage $0 SourceFile" 1>&2 && exit 1
fi

cat $1 > /tmp/main.cpp
cd /tmp

# Default command
echo 'g++-4.7 -Wall -o test main.cpp && ./test' > buildcmd

# Can be overriden
if grep -q "^// g++" main.cpp ; then
    cat main.cpp | head -n1 | sed 's,^//[ ],,' > buildcmd
fi

# Run the command
sh buildcmd
