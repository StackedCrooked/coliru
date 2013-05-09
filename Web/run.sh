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
  echo "Starting web server."
  sudo -u webserver -E shotgun webserver-sinatra.rb -p 80 -o stacked-crooked.com
}

while true ; do
    restart_webserver >webserver.log 2>&1
    echo 'webserver crashed' >webserver.log
    sleep 2
done

