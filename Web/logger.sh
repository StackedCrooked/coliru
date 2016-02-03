#!/bin/bash

cd "$(dirname $0)"

# Kill previous instance of _logger.sh (if any)
ps -eopid,comm | grep '_logger.sh' | grep -v grep | awk '{print $1}' | while read line;  do
     echo "Killing previous instance $line"
     kill -9 $line
done

[ -p .stdout ] || { rm -f .stdout ; mkfifo .stdout ; }
[ -p .stderr ] || { rm -f .stderr ; mkfifo .stderr ; }
chown webserver:coliru .stdout
chown webserver:coliru .stderr

while true ; do
    ./_logger.sh 
done
