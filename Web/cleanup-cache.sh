#!/bin/bash
cache_size () 
{ 
    ls --color=auto ../CompileArchive | wc -l
}

random_cache_entry () 
{ 
    ls --color=auto ../CompileArchive/ | head -n1
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
