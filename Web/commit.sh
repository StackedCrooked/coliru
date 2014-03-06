#!/bin/bash
{
    {
        set -x
        cd $(dirname ${0})
        echo "pwd: $(pwd)"
        echo "ls: $(ls | xargs)"
        for d in $(ls Archive2 | sort -R) ; do
            echo $d
            cd Archive2/$d ; echo "pwd: $(pwd) ; ls:  $(ls | xargs)" ; svn cleanup ; svn add * ; svn ci -m "Update archive $d" ; cd .. ; sleep 2
        done
    } 2>&1 | tee -a commit.log
} & disown
