#!/bin/bash
[ "$(whoami)" == "root" ] || {
echo "$(basename $0) must be run with root permissions." 1>&2
exit 1
}

# Detect already running instance.
pgids="$(ps -eopgid,ppid,pid,uid,comm | grep 'committer.sh' | awk '{print $1}' | sort -n | uniq)"
[ "$(echo "${pgids}" | wc -l)" == 1 ] || {
echo "Committer is already running" 1>&2
exit 1
}

# Output to log files.
source coliru_env.source
source logger.source

# First remove all svn locks.
(
    cd ${COLIRU_ARCHIVE2}

    ls | grep svn_lock | xargs rm -rf

    # Cleanup svn
    svn up
    svn cleanup
    svn up
)
 
commit() {
    svn ci $1 -m "Updating archive." || sleep 1
}

while true ; do (
    cd "${COLIRU_ARCHIVE2}"

    # get day counter
    epoch_days="$(($(date +%s) / (3600 * 24)))"

    # clear any old locks
    for obsolete_lock in $(ls | grep svn_lock | grep -v $epoch_days) ; do
        rm -r $obsolete_lock
    done

    # try to create today's lock
    svn_lock="svn_lock_${epoch_days}"
    mkdir $svn_lock && {
        # we got the lock, ensure it's destroyed on exit
        trap "rm -r $svn_lock" EXIT

        echo "obtained $svn_lock"

        set +x
        for d in $(echo {0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f}{0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f}) ; do
            commit $d || echo "Failed to commit $d" 2>&1
        done
        set -x

        rm -r $svn_lock
    } || echo "Failed to create the lock $svn_lock"
    sleep 3600
) done 
