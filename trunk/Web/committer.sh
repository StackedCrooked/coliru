#!/bin/bash
[ "$(whoami)" == "root" ] || {
echo "$(basename $0) must be run with root permissions." 1>&2
exit 1
}

pgids="$(ps -eopgid,ppid,pid,uid,comm | grep 'committer.sh' | awk '{print $1}' | sort -n | uniq)"
[ "$(echo "${pgids}" | wc -l)" == 1 ] || {
echo "Committer is already running" 1>&2
exit 1
}

source logger.source

set -x
source coliru_env.source

while true ; do (
    cd "${COLIRU_ARCHIVE2}"
    for d in $(ls) ; do 
        # Check if it's a directory (it could be junk)
        if [ ! -d "$d" ] ; then 
            echo "$(pwd) has junk file: $d" 1>&2
            continue
        fi
    done

    mka

    if ! { mkdir svn_lock && trap 'rm -f svn_lock' EXIT ; } ; then
        # another script is using svn return later
        exit 1
    fi

    # we got the lock, ensured it's destroyed on exit

    svn add --force $d >/dev/null 2>&1
    if ! svn ci $d -m "Update archive." ; then 
        # commit failed!
        # => update, cleanup and update again
        svn up
        svn cleanup $d
        svn up

        # svn add will be retried later
        continue

    fi
done) 

# Repeat later. 
sleep 3600
done
