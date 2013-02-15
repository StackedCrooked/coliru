#!/bin/bash
cd "$(dirname $0)"
./kill-current.sh
./environment.sh
./coliru-environment.sh
./repair-permissions.sh 
echo "Starting web server."
sudo -E -u webserver ruby webserver.rb stacked-crooked.com 80
