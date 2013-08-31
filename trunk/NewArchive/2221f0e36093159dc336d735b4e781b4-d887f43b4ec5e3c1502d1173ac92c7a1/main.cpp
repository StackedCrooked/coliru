#!/bin/bash
echo "100 most recent Coliru posts:"
export RECENT_POSTS="$(ls -t /Archive | head -n100)"
for p in ${RECENT_POSTS} ; do printf "$(date -d @$(cat /Archive/${p}/timestamp))\thttp://stacked-crooked.com/view?id=${p}/\n" ; done
