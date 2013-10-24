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


# Clean the chroot tmp folder every 7000 seconds.
{ while true ; do sleep 7000 ; rm -rf /var/chroot/tmp/* ; done ; } & disown

# Clear the coliru temp dir every 7000 seconds 
{ while true ; do sleep 7000 ; rm -rf /tmp/coliru/* ; done ; } & disown

# Clear the compilation cache every week
{
    while true ; do
        sleep $((7 * 24 * 3600))
        mv ../CompileArchive _
        mkdir ../CompileArchive 
        rm -rf _
    done
} & disown
