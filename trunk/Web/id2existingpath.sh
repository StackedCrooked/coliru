#!/bin/bash
source coliru_env.source

# get the path
path=$(./id2path.sh ${1})

# if it exists return it
[ -d "${path}" ] && {
    echo "${path}"
    exit
}

# else return path to the old archive
echo "${COLIRU_ARCHIVE}/${1}"
