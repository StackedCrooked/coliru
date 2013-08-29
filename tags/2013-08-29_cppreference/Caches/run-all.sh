#!/bin/bash
if [ "$(whoami)" != "webserver" ] ; then
    echo "Relaunch as webserver."
    sudo -u webserver $0
    exit
fi

cd $(dirname $0)
nice -n 10 ./timestamp-indexer.sh
