#!/bin/bash
COLIRU=${COLIRU:-${HOME}/coliru}
COLIRU_ARCHIVE=${COLIRU_ARCHIVE:-${COLIRU}/Archive}
echo "Overridable variables related to COLIRU:"
set | grep COLIRU

set -x
cd "$(dirname $0)"
pkill -9 -u sandbox
pkill -9 -u webserver
./repair-permissions.sh 
echo "Starting web server."
sudo -u webserver ruby webserver.rb stacked-crooked.com 80
