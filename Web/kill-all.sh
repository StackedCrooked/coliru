#!/bin/bash
for pid in $(ps -eopid,uid,comm,args | grep '200[12]\|cleanup-cache.sh|run.sh\|pgid_killer.sh\|repair-permissions.sh' | grep -v grep | awk '{print $1}' | sort | uniq) ; do
    echo "Killing pid: ${pid}"
    echo "kill -9 ${pid}"
    kill -9 ${pid}
done
