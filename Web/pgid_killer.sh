#!/bin/bash

[ -p .pgid_killer ] || mkfifo .pgid_killer 
chmod a+w .pgid_killer


while true ; do 
    ./_pgid_killer.sh
    logger "$(basename ${0}): _pgid_killer.sh stopped. Restarting soon." 
    sleep 10
done >/dev/null 2>&1 </dev/null & disown
