#!/bin/bash
export COLIRU=${COLIRU:-${HOME}/coliru}
export COLIRU_ARCHIVE=${COLIRU_ARCHIVE:-${COLIRU}/Archive}
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }
while true ; do
    ./_run.sh
    sleep 2
done
