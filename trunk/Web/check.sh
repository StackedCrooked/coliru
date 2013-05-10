#!/bin/bash

while true  ; do
    IS_RUNNING="$(ps -ef | grep '/usr/bin/ruby1.8' | grep -v grep | wc -l)"
    if [ "${IS_RUNNING}" != "1" ] ; then
        echo "$(date): The server seems to have crashed. Restarting" >> check.log
        ./restart.sh
    fi
    sleep 10
done



