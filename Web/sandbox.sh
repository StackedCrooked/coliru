#!/bin/bash
set -e
source coliru_env.source

[ "$INPUT_FILES_DIR" == "" ] && { echo "INPUT_FILES_DIR not set." 1>&2 ; exit 1 ; }

ID="$(./hash.sh)"

# Check archive for previous result.
[ -f "${COLIRU_ARCHIVE}/${ID}/output" ] && cat ${COLIRU_ARCHIVE}/${ID}/output && exit
[ -f "${COLIRU_ARCHIVE_RECENT}/${ID}/output" ] && cat ${COLIRU_ARCHIVE}/${ID}/output && exit

# Launch the chroot
./build_and_run.sh
