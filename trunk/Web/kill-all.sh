#!/bin/bash
for i in `seq 4` ; do 
    ps -ef | grep ^200[12] | grep -v grep |  awk '{print $2}' | xargs -I {} bash -c "echo Killing {} && kill -9 {}"
    ps -ef | grep run.sh   | grep -v grep |  awk '{print $2}' | xargs -I {} bash -c "echo Killing {} && kill -9 {}"
    ps -ef | grep committer.sh   | grep -v grep |  awk '{print $2}' | xargs -I {} bash -c "echo Killing {} && kill -9 {}"
done
