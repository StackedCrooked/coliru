#!/bin/bash
set -e
source coliru_env.source

[ "$INPUT_FILES_DIR" == "" ] && { echo "INPUT_FILES_DIR not set." 1>&2 ; exit 1 ; }

ID="$(./hash.sh)"

# 
# Check archive for previous result.
#
if [ -f "${COLIRU_ARCHIVE}/${ID}/output" ] ; then
    cat "${COLIRU_ARCHIVE}/${ID}/output"
    exit
fi

#
# Reset the timeout to 20 seconds after this script exits.
#
trap "echo 20 > timeout.txt ; exit" INT TERM EXIT


./build_and_run.sh
