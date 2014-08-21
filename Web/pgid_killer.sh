#!/bin/bash

# FIXME: This seems to block the loop
#source logger.source


loop() { 
    rm -f .pgid_killer
    mkfifo .pgid_killer
    chmod a+w .pgid_killer

    while true ; do
        read line <.pgid_killer
        echo "$(basename $0): request for killing pgid $line"
        [ "$line" != "" ] && {
            kill -9 -${line}
        }
    done 
}

while true ; do
    (loop)
    echo "$(basename ${0}): broken out of loop"
    sleep 10
done

