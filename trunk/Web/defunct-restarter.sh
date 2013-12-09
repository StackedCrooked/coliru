#!/bin/bash

source logger.source

while true ; do
    count="$(ps -ef | grep 'sandbox\|2002\|2001' | wc -l)"
    if [ $count -gt 20 ] ; then
        echo "There are $count processes. This is suspiciously high. I will restart the webserver."
        setsid ./restart.sh & disown
    fi
    sleep 60
done
