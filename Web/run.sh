#!/bin/bash
source "./coliru_env.source"
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }
nohup ./committer.sh >/dev/null 2>&1 &
while true ; do
    ./_run.sh
    sleep 2
done
