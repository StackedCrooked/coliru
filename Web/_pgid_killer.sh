#!/bin/bash

cd "$(dirname $0)"

while true ; do 
    while read line ;do
        [ "$line" != "" ] && {
            kill -9 -${line}
        }
    done <.pgid_killer
    sleep 10
done

