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
        sleep 5
        echo "Restarting webserver."
    done
) & disown



echo "Starting committer.sh if not already started."
COMMITTER_PGID=$(ps -eopgid,comm | grep 'committer.sh' | sort | uniq | awk '{ print $1 }')
if [ "$COMMITTER_PGID" == "" ] ; then 
    echo "committer.sh not yet running => start it"
    ./committer.sh & disown
else
    echo "committer.sh already running => don't start it."
fi


# Clean the chroot tmp folder after 1000 seconds.
{ sleep 1000 ; rm -rf /var/chroot/tmp/* ; } & disown

# Clear the coliru temp dir after 1000 seconds 
{ sleep 1000 ; rm -rf /tmp/coliru/* ; } & disown

# Restart after 2000 seconds
#{ sleep 2000 ; ./restart.sh ; } & disown

# Reboot after 5000 seconds
#{ sleep 5000 ; reboot ; } & disown

# Start the pgid killer (for killing timed out sandbox processes)
./pgid_killer.sh & disown

# Start the pid killer (for defunct webserver processes)
./pid_killer.sh & disown

# Start cache-cleanup script
./cleanup-cache.sh & disown

