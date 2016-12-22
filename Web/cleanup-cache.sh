#!/bin/bash
source logger.source

cache_size () 
{ 
    ls  ../CompileArchive | wc -l
}

max=1000


while true ; do
    [ "$(($(cache_size) > $max))" == "1" ] && {
        ls ../CompileArchive | sort -R | head -n50 | while read line ; do
            cmd="rm -rf ../CompileArchive/$line"
            echo "$cmd"
            $cmd
        done
        continue
    } || {
        echo "$0: $(cache_size) <= $max. Ok allow cache to grow."
    }
    sleep 300
done
