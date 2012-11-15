#!/bin/bash
if [[ `uname` == "Linux" ]] ; then
    md5sum $1 | cut -d ' ' -f 1
elif [[ `uname` == "Darwin" ]] ; then
    md5 $1 | cut -d ' ' -f 4
else
    echo "Invalid platform!" 1>&2
fi
