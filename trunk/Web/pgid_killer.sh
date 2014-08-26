#!/bin/bash

[ -p .pgid_killer ] || mkfifo .pgid_killer 
chmod a+w .pgid_killer


while true ; do 
    ./_pgid_killer.sh
    logger "$(basename ${0}): _pgid_killer.sh stopped. Restarting soon." 
    sleep 10
done
