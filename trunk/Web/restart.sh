#!/bin/bash

pkill -u 2001
pkill -u 2002

# Kill previous instance of _restart.sh (if any)
ps -eopid,comm | grep '_restart.sh' | grep -v grep | awk '{print $1}' | while read line;  do
     echo "Killing previous instance $line"
     kill -9 $line
done

setsid ./_restart.sh & disown
