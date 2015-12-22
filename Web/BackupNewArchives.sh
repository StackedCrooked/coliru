#!/bin/bash

[ -d ../Archive2 ] || {
    echo "Archive2 directory not found. Exiting." >&2
    exit 1
}

[ -d ../tArchive2 ] || {
    echo "tArchive2 directory not found. Exiting." >&2
    exit 1
}

[ -f tmp_Archive2.log ] && {
    sort -R tmp_Archive2.log ../Archive2.log -o tmp_Archive2.log 
} || {
    sort -R ../Archive2.log -o tmp_Archive2.log
}

# empty the file without changing permissions
printf "" >../Archive2.log


backup() {
    # gets the 'ab' part from '/root/etc/../ab/cdefghij'
    p1="$(basename $(dirname $@))"
    #p2="$(basename $@)"
    (set -x && cd .. && tar -czf "tArchive2/$p1.tar.gz" "Archive2/$p1")
}

{ cat tmp_Archive2.log | while read line ; do [ "$line" != "" ] && backup "$line" ; done ;  } && rm tmp_Archive2.log 
