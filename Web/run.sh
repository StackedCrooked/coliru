#!/bin/bash
./repair-permissions.sh >/dev/null 2>&1
setsid sudo -u webserver -E bash -c "
    exec > >(logger -t $0) 2>&1 
    ruby webserver-sinatra.rb -o stacked-crooked.com
    "
