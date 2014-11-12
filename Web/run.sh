#!/bin/bash
source coliru_env.source
source logger.source

while true ; do 
    sudo -u webserver -E ruby webserver-sinatra.rb -o "${COLIRU_URL}"
    echo "RESTARTING WEBSERVER SOON"
    sleep 5
done
