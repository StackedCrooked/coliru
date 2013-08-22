#!/bin/bash
if [ "$(whoami)" != "webserver" ] ; then
    echo "The indexer must be run by the webserver." 1>&2
    exit 1
fi
cd $(dirname $0)

for ts in $(find ../Archive -name timestamp) ; do
    printf "$(cat $ts) $(dirname $ts)\n" >>_timestamp_to_directory
done

