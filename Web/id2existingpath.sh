#!/bin/bash
source coliru_env.source

# get the path (Archive3)
path=$(./id2path.sh ${1})
[ -d "${path}" ] && { echo "${path}"; exit; }

# try Archive2
path2="${COLIRU_ARCHIVE2}/$(./pathify-id.sh ${1})"
[ -d "${path2}" ] && { echo "${path2}"; exit; }

# else return path to the old archive (non-pathified)
echo "${COLIRU_ARCHIVE}/${1}"
