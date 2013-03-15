#!/bin/bash
source "./coliru_env.source"
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }

restart_webserver() {
  source ./coliru_env.source
  cd "$(dirname $0)"
  ./kill-current.sh
  ./repair-permissions.sh 
  echo "Starting web server."
  sudo -E -u webserver ruby webserver-sinatra.rb >coliru.log 2>&1
}

while true ; do
    restart_webserver
    sleep 2
done

