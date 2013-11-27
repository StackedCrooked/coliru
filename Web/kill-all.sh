#!/bin/bash
for PGID in $(ps -eopgid,uid,comm | grep '200[12]\|defunct\|committer.sh' | awk '{print $1}' | sort | uniq) ; do
    echo "Killing PGID: ${PGID}"
    kill -9 -${PGID}
done
