#!/bin/bash
source ./coliru_env.source
cd "$(dirname $0)"
./kill-current.sh
./repair-permissions.sh 
echo "Starting web server."
sudo -E -u webserver ruby webserver-sinatra.rb >coliru.log 2>&1
