#!/bin/bash
{
    cd $(dirname ${0})
    while true ; do
        for d in $(ls Archive2 | sort -R) ; do
            (set -x; cd Archive2/$d ; { svn add * 2>/dev/null && { { sleep 5 && svn ci -m "Update archive $d" ; } || { svn cleanup && sleep 5 && svn up ; } ; } ; }; chown -R webserver:coliru .)
            sleep 10
        done 2>&1 | tee -a _svn-commit.log
        echo "sleeping for 3600 seconds"
        sleep 3600
    done
} & disown

