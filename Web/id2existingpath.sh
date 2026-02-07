#!/bin/bash
source coliru_env.source

id="$1"
pathifiedId="$(./pathify-id.sh "${id}")"

# Prefer the newest archive first.
[ -d "${COLIRU_ARCHIVE3}/${pathifiedId}" ] && {
    echo "${COLIRU_ARCHIVE3}/${pathifiedId}"
    exit
}

[ -d "${COLIRU_ARCHIVE2}/${pathifiedId}" ] && {
    echo "${COLIRU_ARCHIVE2}/${pathifiedId}"
    exit
}

[ -d "${COLIRU_ARCHIVE}/${id}" ] && {
    echo "${COLIRU_ARCHIVE}/${id}"
    exit
}

# Default to the newest location for new writes.
echo "${COLIRU_ARCHIVE3}/${pathifiedId}"
