#!/bin/bash

# Start the webserver
for i in {1..10} ; do 
    for i in {1..10} ; do
        pkill -u 2001
        ./run.sh
        echo "WEBSERVER STOPPED. RESTARTING WEBSERVER IMMEDIATELY"
    done
    echo "RESTARTING WEBSERVER NOW"
    sleep 60
done

echo "TOO MANY RESTARTS. REBOOTING SOON."
sleep 300
reboot

