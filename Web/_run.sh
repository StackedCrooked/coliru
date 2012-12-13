#!/bin/bash
set -x
cd "$(dirname $0)"
pkill -9 -u sandbox
pkill -9 -u webserver
./repair-permissions.sh 
sudo -u webserver ruby webserver.rb stacked-crooked.com 80
