#!/bin/bash
cache_size () 
{ 
    ls  ../CompileArchive | wc -l
}

random_cache_entry () 
{ 
    random_index="$(($RANDOM % $(cache_size)))"
    ls ../CompileArchive | head -n $random_index | tail -n1
}


max=5000


while true ; do
    [ "$(($(cache_size) > $max))" == "1" ] && {
        echo "$(cache_size) > $max => delete $(random_cache_entry)"
        rm -rf ../CompileArchive/$(random_cache_entry)
    } || {
        echo "$(cache_size) <= $max. Ok allow cache to grow."
    }
    sleep 1
done
