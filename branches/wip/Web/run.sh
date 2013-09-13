#!/bin/bash
source coliru_env.source
source logger.source

if [ "$(whoami)" != "root" ] ; then
    echo "$(basename $0) must be run with root permissions." 1>&2
    exit 1
fi

./repair-permissions.sh & disown
setsid sudo -u webserver -E ruby webserver-sinatra.rb -o ${COLIRU_URL}
