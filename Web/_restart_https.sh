#!/bin/bash

# Copy certificate and private key to current directory
# (because user "webserver" can't access the letsencrypt dir)
cp /etc/letsencrypt/live/stacked-crooked.com/fullchain.pem .
cp /etc/letsencrypt/live/stacked-crooked.com/privkey.pem . 


# Start the webserver
for i in {1..10} ; do 
    for i in {1..10} ; do
        COLIRU_PORT=443 COLIRU_CERTIFICATE=fullchain.pem COLIRU_PRIVATE_KEY=privkey.pem ./run.sh
        echo "HTTPS (443) WEBSERVER STOPPED. RESTARTING WEBSERVER IMMEDIATELY" >>output.log 2>&1
    done
    echo "RESTARTING WEBSERVER NOW"
    sleep 60
done

echo "TOO MANY RESTARTS. REBOOTING SOON."
sleep 300
reboot

