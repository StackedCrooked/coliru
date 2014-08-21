#!/bin/bash

cd "$(dirname $0)"

log() {
    echo "$1"
    logger "$1"
}

log "$(basename $0) started"


rm -f .stdout
mkfifo .stdout
chown webserver:coliru .stdout

while true ; do
    while read line ; do 
        log ".stdout: $line"
    done <.stdout
    log "Finished logging"
done
