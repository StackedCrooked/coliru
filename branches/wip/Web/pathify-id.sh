#!/bin/bash
set -e

[ "$#" == "1" ] || {
    echo "Usage $(basename $0) Id" 1>&2
    exit 1
}

[ "$(echo "${id}" | grep '\/')" == "" ] && {
    # Split the id in dir and subdir
    dir="$(echo "$1" | cut -c -2)"
    subdir="${1:2}"
    echo "${dir}/${subdir}"
    exit
}

# The id was already split
echo "${1}"
