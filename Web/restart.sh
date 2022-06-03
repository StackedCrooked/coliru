#!/bin/bash
source coliru_env.source


pkill -u 2001


# Kill previous instance of _restart.sh (if any)
ps -eopid,comm | grep '_restart' | grep -v grep | awk '{print $1}' | while read line;  do
     echo "Killing previous instance $line"
     kill -9 $line
done


# Setup directories and set permissions
rm -rf /tmp/coliru ; mkdir -p /tmp/coliru ; chown -R webserver:coliru /tmp/coliru
rm -f /tmp/cleanup ; touch /tmp/cleanup ; chown webserver:coliru /tmp/cleanup
chown -R webserver:coliru /tmp


# Start HTTP server
setsid ./_restart_http.sh & disown


# Start HTTPS server
setsid ./_restart_https.sh & disown


{ sleep $((5 * 24 * 3600)) ; reboot ; } & disown
