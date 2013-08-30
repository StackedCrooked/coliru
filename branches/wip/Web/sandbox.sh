#!/bin/bash

# Enforce sequential access to the sandbox.
while  ! mkdir $0.lock 2>/dev/null ; do sleep 1 ; done
trap 'rm -rf "$0.lock"' EXIT

set -e
source coliru_env.source

[ "$INPUT_FILES_DIR" == "" ] && { echo "INPUT_FILES_DIR not set." 1>&2 ; exit 1 ; }

ID="$(./hash.sh)"

# Check archive for previous result.
[ -f "${COLIRU_ARCHIVE}/${ID}/output" ] && cat ${COLIRU_ARCHIVE}/${ID}/output && exit
[ -f "${COLIRU_ARCHIVE_RECENT}/${ID}/output" ] && cat ${COLIRU_ARCHIVE}/${ID}/output && exit

# Launch the chroot
./build_and_run.sh
