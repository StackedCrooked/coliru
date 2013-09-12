#!/bin/bash

# Check arguments
[ "$#" == "1" ] || {
    echo "Usage: $(basename $0) ArchivePath" 1>&2
    exit 1
}

if [ "$(whoami)" != "webserver" ] ; then
    echo "Restarting $(basename $0) as webserver user." 1>&2
    sudo -u webserver bash $0 $1
    exit
fi

(
    cd $(dirname $0)
    {
        while read ts ; do
            printf "$(cat ${ts}) $(dirname ${ts})\n"
        done < <(find "${1}" -name timestamp) 
    } >_timestamp_to_directory
)
