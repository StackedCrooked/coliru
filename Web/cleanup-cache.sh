#!/bin/bash
source coliru_env.source
source logger.source

mkdir -p "${COLIRU_COMPILE_CACHE}"

cache_size () 
{ 
    ls "${COLIRU_COMPILE_CACHE}" | wc -l
}

max=1000


while true ; do
    [ "$(($(cache_size) > $max))" == "1" ] && {
        ls "${COLIRU_COMPILE_CACHE}" | sort -R | head -n50 | while read line ; do
            cmd="rm -rf ${COLIRU_COMPILE_CACHE}/$line"
            echo "$cmd"
            $cmd
        done
        continue
    } || {
        echo "$0: $(cache_size) <= $max. Ok allow cache to grow."
    }
    sleep 300
done
