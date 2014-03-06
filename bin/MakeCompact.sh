#!/bin/bash
[ "$#" == "1" ] || {
    echo "Usage: $(basename $0) archive_dir." 1>&2
    echo "Example: $(basename $0) 02/06521fc28ade03" 1>&2
    exit 1
}

cd "$1" && ls  -1 | while read line ; do echo "$line $(cat $line | /usr/bin/base64 --break=0)" ; done
