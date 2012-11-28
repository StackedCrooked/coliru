#!/bin/bash
mkdir -p Archive
if [ "$(uname)" == "Darwin" ] ; then 
    ID="$(md5 main.cpp | cut -d '=' -f 2 | sed -e 's/ //g')"
else
    ID="id_is_md5"
fi

if [ -d "Archive/${ID}" ] ; then
    echo ${ID}
    exit
fi

DIR="Archive/${ID}"
mkdir "${DIR}"


if [ "$(uname)" == "Darwin" ] ; then 
    cat main.cpp > "${DIR}/main.cpp"
    CMD="g++ -std=c++0x -o test -pthread main.cpp"
    ${CMD} > "${DIR}/output"
    ./test  >> "${DIR}/output"
    echo ${ID}
    exit 0
fi
