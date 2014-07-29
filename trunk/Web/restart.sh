#!/bin/bash

source coliru_env.source
source logger.source

if [ "$(whoami)" != "root" ] ; then
    echo "$(basename $0) must be run with root permissions." 1>&2
    exit 1
fi


cd $(dirname $0)


echo "Killing any previously running instances..."
./kill-all.sh >/dev/null 2>&1


echo "Starting new instance..."
(
    source logger.source
    while true ; do
        ./run.sh && echo "*** WEBSERVER QUIT! *** " || echo "*** WEBSERVER CRASHED! ***" 1>&2
        sleep 60
        echo "Restarting webserver."
    done
) & disown


# Start the pgid killer (for killing timed out sandbox processes)
./pgid_killer.sh & disown

# Start cache-cleanup script
./cleanup-cache.sh & disown

# Start the defunct processes monitor
./defunct-restarter.sh & disown

# Disable network access
iptables -A OUTPUT -m owner --uid-owner 2002 -j DROP

# Schedule a future reboot (because we crash all the time)
setsid bash -c "sleep $((1 * 3600)) ; reboot" & disown
