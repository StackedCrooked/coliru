#!/bin/bash
if [ "$(whoami)" != "webserver" ] ; then
    echo "The indexer must be run by the webserver." 1>&2
    exit 1
fi

cd $(dirname $0)
nice -n 10 ./timestamp-indexer.sh
