#!/bin/bash

source logger.source

while true ; do
    count="$(ps -ef | grep 'sandbox\|2002\|2001' | wc -l)"
    if [ $count -gt 50 ] ; then
        echo "There are $count processes. This is suspiciously high. I will reboot the webserver in 5 minutes."
        { sleep 300 ; reboot ; } & disown
    else
        echo "There are $count processes. This may still grow."
    fi
    sleep 120
done
