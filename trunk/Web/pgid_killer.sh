#!/bin/bash
set -x
source logger.source

rm -f .pgid_killer
mkfifo .pgid_killer
chmod a+w .pgid_killer
while true ; do
    read line <.pgid_killer
    [ "$line" != "" ] && {
        echo "Killing sandbox process: $line"
        kill -9 "$line" 
    } || {
        echo "Nothing to kill."
    }
done 
