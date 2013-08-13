#!/bin/bash
#set -x
if [ "$(whoami)" != "root" ] ; then
    echo "The restart script must be run as root." 1>&2
    exit 1 
fi


source ./coliru_env.source
env | grep COLIRU


NUM_RESTART_PROCESSES=$(./ps.sh | grep $(basename $0) | awk '{print $1}' | sort | uniq | wc -l)
if [ "$NUM_RESTART_PROCESSES" != "1" ] ; then
    echo "Killing the restarters (myself included)."
    echo "PLEASE RESTART THIS SCRIPT!"
    ALREADY_RUNNING=$(./ps.sh | grep $(basename $0) | awk '{print $1}' | sort | uniq)
    if [ "$ALREADY_RUNNING" != "" ] ; then
        echo "Killling previous instance with pgid: ${ALREADY_RUNNING}."
        kill -9 -${ALREADY_RUNNING}
        exit
    else
        echo "OK. This script is not yet running."
    fi
fi


echo "SUCCESS"
{ while true ; do
    ./run.sh
    echo "Program quit for unknown reason."
    DURATION=10
    echo "Restarting with ${DURATION} seconds."
    sleep $DURATION
done ; } & disown
