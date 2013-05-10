#!/bin/bash
while true  ; do
    IS_RUNNING="$(ps -ef | grep '/usr/bin/ruby1.8' | grep -v grep | wc -l)"
    if [ "${IS_RUNNING}" != "1" ] ; then
        echo "The server seems to have crashed." 1>&2
        ./restart.sh
    else
        echo "Ok. It is running"
    fi
    sleep 10
done



