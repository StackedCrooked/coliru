#!/bin/bash
if [ "$(whoami)" != "webserver" ] ; then
    echo "The indexer must be run by the webserver." 1>&2
    exit 1
fi
cd $(dirname $0)

find ../Archive -name timestamp >_timestamps
while read line ; do
    printf "$(cat $entry)_$(dirname $entry)\n" >_timestamp_to_directory
done <_timestamps

