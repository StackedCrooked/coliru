#!/bin/bash

cd "$(dirname $0)"

log() {
    echo "$1"
    logger "$1"
}

log "$(basename $0) started"


make_stdout() {
    rm -f stdout
    mkfifo stdout
    chown webserver:coliru stdout
}

make_stdout

while true ; do

    # remake the stdout file if it no longer exists for some reason
    [ -f stdout ] || make_stdout
    
    while read line ; do 
        log "stdout: $line"
    done <stdout
    log "Broke out of stdout loop"
    sleep 2
done
