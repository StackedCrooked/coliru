#!/bin/bash
source coliru_env.source
source logger.source

while true ; do 
    sleep 3600
    echo "Hourly restart."
    ./do_restart.sh
done & disown
