#!/bin/bash

# Start the webserver
for i in {1..10} ; do 
    for i in {1..10} ; do
        ./run.sh
        echo "HTTP (80) WEBSERVER STOPPED. RESTARTING WEBSERVER IMMEDIATELY" >>output.log 2>&1
    done
    echo "RESTARTING WEBSERVER NOW"
    sleep 60
done

echo "TOO MANY RESTARTS. REBOOTING SOON."
sleep 300
reboot

