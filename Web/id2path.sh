#!/bin/bash
[ "$#" != "1" ] && {
    echo "Usage: $(basename $0) id" 1>&2
    exit 1
}

set -e
source coliru_env.source

id="$(./pathify-id.sh $1)"
#echo "${COLIRU_ARCHIVE}/${id}"
echo "${COLIRU_ARCHIVE2}/${id}"
