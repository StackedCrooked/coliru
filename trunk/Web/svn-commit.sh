#!/bin/bash
rp() { chown -R webserver:coliru . ; }

{
    set -x
    cd $(dirname ${0})
    while true ; do
        for d in $(ls Archive2 | sort -R) ; do (
            set -x;
            cd Archive2/$d 
            [ "$(svn st | wc -l)" == "0" ] || {
                echo "Found stuff. Try to svn add it."
                svn add *
                [ "$(svn st | wc -l)" == "0" ] || {
                    { echo "I have stuff to commit!" && sleep 5 && svn ci -m "Update archive $d" && rp; } ||
                    { echo "Commit failed!" && svn cleanup && sleep 5 && svn up ; rp; }
                }
            }
            sleep $((10 + $(($RANDOM % 20))))
        )
        done 2>&1 | tee -a _svn-commit.log
        echo "sleeping for 3600 seconds"
        sleep 3600
    done
} & disown
