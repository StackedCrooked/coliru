#!/bin/bash
source ./coliru_env.source

NUM_RESTART_PROCESSES=$(./ps.sh | grep $(basename $0) | awk '{print $1}' | sort | uniq | wc -l)
if [ "$NUM_RESTART_PROCESSES" != "1" ] ; then
    echo "Killing the restarters (myself included)."
    echo "PLEASE RESTART THIS SCRIPT!"
    ./ps.sh | grep $(basename $0) | awk '{print $1}' | sort | uniq | xargs -I {} kill -9 -{}
    exit
fi


echo "SUCCESS"
./killuid.sh 2001 ; ./killuid.sh 2002
{ while true ; do ./run.sh ; done ; } & disown
