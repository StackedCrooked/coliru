#!/bin/bash
set -x
cd $(dirname $0)

find ../Archive -name timestamp >_timestamps
while read line ; do
    printf "$(cat $entry)_$(dirname $entry)\n" >_timestamp_to_directory
done <_timestamps

