#!/bin/bash
while true  ; do
    IS_RUNNING="$(ps -ef | grep '/usr/bin/ruby1.8' | grep -v grep | wc -l)"
    echo "$(date): Check status: ${IS_RUNNING}"
    if [ "${IS_RUNNING}" != "1" ] ; then
        echo "$(date): The server seems to have crashed. Restarting"
        ./restart.sh
    else
        echo "$(date): Server is still running fine."
    fi
    sleep 60
done
