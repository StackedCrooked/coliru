#!/bin/bash
source coliru_env.source
source logger.source

# Cleanup coliru processes
pkill -u 2002
pkill -u 2001


# Setup directories and set permissions
rm -rf /tmp/coliru ; mkdir -p /tmp/coliru ; chown -R webserver:coliru /tmp/coliru
rm -f /tmp/cleanup ; touch /tmp/cleanup ; chown webserver:coliru /tmp/cleanup
chown -R webserver:coliru /tmp

# Disable network access
iptables -A OUTPUT -m owner --uid-owner 2002 -j DROP

# Start the webserver

num_restarts=0
while true ; do 
    num_restarts="$(($num_restarts + 1))"
    echo "*** STARTING WEBSERVER (num_restarts=${num_restarts}) ***"
    ./run.sh && {
        echo "*** WEBSERVER STOPPED: $? "
    } || {
        echo "*** WEBSERVER CRASHED: $? "
    }

    pkill -u 2002
    pkill -u 2001

    # Prevent spinning in case something is wrong
    sleep 10
done & disown
