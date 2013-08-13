#!/bin/bash
#set -x
exec > >(logger -t $0) 2>&1
./repair-permissions.sh
if [ "$(hostname)" == "stacked-crooked" ] ; then
    URL="stacked-crooked.com"
else
    IP="$(ifconfig | grep 'inet addr:' | head -n1 | perl -pe 's,.*addr:(\d+\.\d+\.\d+\.\d+).*,\1,')"
    URL="${IP}"
fi
echo "Binding: ${URL}"


sudo -u webserver ruby webserver-sinatra.rb -o ${URL}
