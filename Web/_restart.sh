#!/bin/bash
source coliru_env.source
source logger.source



# Setup directories and set permissions
rm -rf /tmp/coliru ; mkdir -p /tmp/coliru ; chown -R webserver:coliru /tmp/coliru
rm -f /tmp/cleanup ; touch /tmp/cleanup ; chown webserver:coliru /tmp/cleanup
chown -R webserver:coliru /tmp

# Disable network access
/sbin/iptables -A OUTPUT -m owner --uid-owner 2002 -j DROP

# Start the webserver
for i in {1..10} ; do 
    for i in {1..10} ; do
        pkill -u 2002
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

