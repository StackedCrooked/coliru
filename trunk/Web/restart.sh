#!/bin/bash

source coliru_env.source
source logger.source
 
if [ "$(whoami)" != "root" ] ; then
    echo "$(basename $0) must be run with root permissions." 1>&2
    exit 1
fi


cd $(dirname $0)


# Kill any previously running instances
./kill-all.sh >/dev/null 2>&1


# Setup directories and set permissions
rm -rf /tmp/coliru ; mkdir -p /tmp/coliru ; chown -R webserver:coliru /tmp/coliru
rm -f /tmp/cleanup ; touch /tmp/cleanup ; chown webserver:coliru /tmp/cleanup
chown -R webserver:coliru /tmp

# Check/repair permissions
./repair-permissions.sh & disown

# Start the pgid killer (for killing timed out sandbox processes)
./pgid_killer.sh & disown

# Start cache-cleanup script
./cleanup-cache.sh & disown

# Disable network access
iptables -A OUTPUT -m owner --uid-owner 2002 -j DROP

# Start the webserver
./run.sh & disown

# Schedule a future reboot (because we crash all the time)
setsid bash -c "sleep $((1 * 3600)) ; reboot" & disown
