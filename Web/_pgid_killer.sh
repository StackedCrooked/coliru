#!/bin/bash

while true ; do 
    while true ; do
        read line <.pgid_killer
        echo "$(basename $0): request for killing pgid '$line'"
        [ "$line" != "" ] && {
            kill -9 -${line}
        }
    done 
    logger "$(basename ${0}): *** BROKEN LOOP **** "
    sleep 10
done

logger "$(basename $0): *** EXITED ***"
