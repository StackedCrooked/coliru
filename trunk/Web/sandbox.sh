#!/bin/bash

set -e
source coliru_env.source

# check if INPUT_FILES_DIR is set.
[ "$INPUT_FILES_DIR" == "" ] && { echo "INPUT_FILES_DIR not set." 1>&2 ; exit 1 ; }

# get the id (a on hash of main.cpp and cmd.sh)
id="$(./hash.sh)"

# search for previous result in the old archive
[ -d ${COLIRU_ARCHIVE}/${id} ] && {
    cat "${COLIRU_ARCHIVE}/${id}/output"
    #echo "(found in old archive)" 1>&2
    exit
}

# search for previous output in the new archive
pathifiedId="$(./pathify-id.sh ${id})"
[ -d "${COLIRU_ARCHIVE2}/${pathifiedId}" ] && {
    cat "${COLIRU_ARCHIVE2}/${pathifiedId}/output"
    #echo "(found in new archive)" 1>&2
    exit
}

# no previous result found => compile it and print the output
./build_and_run.sh
