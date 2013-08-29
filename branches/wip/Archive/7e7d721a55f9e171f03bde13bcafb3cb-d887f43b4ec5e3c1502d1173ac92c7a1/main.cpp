#!/bin/bash
export RECENT_POSTS="$(ls -t /Archive | head -n10)"
for p in ${RECENT_POSTS} ; do printf "$(date -d @$(cat /Archive/${p}/timestamp))\t/Archive/${p}/\n" ; done
