#!/bin/bash
set -x
set -e
[ "`whoami`" == "root" ] || { echo "This program must be run by root." 1>&2 ; exit 1; }
source "./coliru_env.source"
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }

restart_webserver() {
  source ./coliru_env.source
  cd "$(dirname $0)"
  ./kill-current.sh
  ./repair-permissions.sh 
  echo "$(date): Starting web server." >>webserver.log 2>&1
  { sudo -u webserver -E shotgun webserver-sinatra.rb -p 80 -o stacked-crooked.com ; } >>webserver.log 2>&1
}

while true ; do
    restart_webserver >>webserver.log 2>&1
    echo "$(date): webserver crashed" >>webserver.log 2>&1
    sleep 2
done

