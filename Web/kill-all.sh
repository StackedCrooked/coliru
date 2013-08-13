#!/bin/bash
for PGID in $(ps -eopgid,uid | grep '200[12]' | awk '{print $1}' | sort | uniq) ; do
    echo "Killing PGID: ${PGID}"
    kill -9 -${PGID}
done
