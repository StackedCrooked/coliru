#!/bin/bash
#set -x
if [ "$(whoami)" != "root" ] ; then
    echo "$(basename $0) must be run with root permissions." 1>&2
    exit 1
fi

source coliru_env.source
./repair-permissions.sh
setsid sudo -u webserver -E bash -c "
    exec > >(logger -t $0) 2>&1 
    ruby webserver-sinatra.rb -o ${COLIRU_URL}
    "
