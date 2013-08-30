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

exec 1> >(logger -t "$0 stdout")
exec 2> >(logger -t "$0 stderr")

set -x
source coliru_env.source
[ -z ${COLIRU_ARCHIVE_RECENT} ] && { echo "COLIRU_ARCHIVE_RECENT variable must be set." && exit 1; }
[ -d ${COLIRU_ARCHIVE_RECENT} ] || { echo "${COLIRU_ARCHIVE_RECENT} does not exist. Exiting." && exit 1 ; }

while true ; do

    (
        cd ${COLIRU_ARCHIVE_RECENT}

        for d in $(ls) ; do 
            [ -d $d ] && {
                # Commit new
                svn ci $d -m "Update archive."
                [ "$(svn st $d 2>&1)" == "" ] && {
                    (cd ${COLIRU_ARCHIVE} && svn up $d) && rm -rf $d && svn cleanup && svn up
                } || {
                    echo "$d seems to have a problem $(svn st $d 2>&1)" 1>&2
                }
            } || {
                echo "$d is not a directory." 1>&2
            }
        done
    ) 

    # Repeat later. 
    sleep 3600
done
