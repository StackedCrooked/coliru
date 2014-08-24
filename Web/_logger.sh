#!/bin/bash

cd "$(dirname $0)"

log() {
    # NOTE: we must have a prefix (like stdout:) in 
    # order to prevent initial -- to be interpreted
    # as command argumn."
    echo "stdout: $@"
    logger "stdout: $@"
}

log "$(basename $0) started"


rm -f .stdout
mkfifo .stdout
chown webserver:coliru .stdout

while true ; do
    while read line ; do 
        log "$line"
    done <.stdout
done
