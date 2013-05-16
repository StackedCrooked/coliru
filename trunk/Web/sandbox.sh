#!/bin/bash
set -e
source coliru_env.source


[ "$INPUT_FILES_DIR" == "" ] && { echo "INPUT_FILES_DIR not set." 1>&2 ; exit 1 ; }

if [ -f "${INPUT_FILES_DIR}/main.cpp" ] ; then
    ID="$(md5sum ${INPUT_FILES_DIR}/main.cpp | cut -d ' ' -f 1)-$(md5sum ${INPUT_FILES_DIR}/cmd.sh | cut -d ' ' -f 1)"
else
    ID="$(md5sum ${INPUT_FILES_DIR}/cmd.sh | cut -d ' ' -f 1)"
fi

if [ -f "${COLIRU_ARCHIVE}/${ID}/output" ] ; then
    cat "${COLIRU_ARCHIVE}/${ID}/output"
    exit
fi

trap "echo 20 > timeout.txt ; exit" INT TERM EXIT

./build_and_run.sh
