#!/bin/bash
wget -q -O - "http://stackoverflow.com/questions" \
    | egrep -e '/questions/[0-9]+' \
    | perl -p -e 's,.*href="(.+)".*,\1,g' \
    | xargs -I {} echo "http://stackoverflow.com{}" \
    | xargs -I {} echo {} > urls

for url in `cat urls` ; do 
    echo $url \
    | grep -v ^class \
    | xargs -I {} bash -c "sleep 1 ; open \"{}\" ; echo wait ; sleep 2 "
done
