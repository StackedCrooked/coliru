#!/bin/bash
[ -z "$COLIRU" ] && { echo "COLIRU environment variable needs to be set." && exit 1 ; }
cd "$(dirname $0)"
./kill-current.sh
./repair-permissions.sh 
echo "Starting web server."
sudo -E -u webserver ruby webserver.rb stacked-crooked.com 80
