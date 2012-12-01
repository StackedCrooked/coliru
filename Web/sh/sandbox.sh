#!/bin/bash
if [ "$(uname)" == "Darwin" ] ; then 
    ID="$(md5 main.cpp | cut -d '=' -f 2 | sed -e 's/ //g')"
else
    ID="$(md5sum main.cpp | cut -d ' ' -f 1)"
fi

if [ -f "Archive/${ID}/output" ] ; then
    cat "Archive/${ID}/output"
    exit
fi

./build_and_run.sh
