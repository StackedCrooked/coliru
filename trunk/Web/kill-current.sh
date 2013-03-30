#!/bin/bash
for i in `seq 4` ; do 
    echo "Iteration $i"
    pkill -u 2002
    pkill -u 2001
    ps -ef | grep ^200[12] | grep -v grep |  awk '{print $2}' | xargs -I {} bash -c "echo Killing {} && kill -9 {}"
done
