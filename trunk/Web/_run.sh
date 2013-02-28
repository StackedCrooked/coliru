#!/bin/bash
source ./coliru_env.source
cd "$(dirname $0)"
./kill-current.sh
./repair-permissions.sh 
echo "Starting web server."
sudo -E -u webserver ruby webserver.rb "${COLIRU_URL}" "${COLIRU_PORT}"
