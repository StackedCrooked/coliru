#!/bin/bash
cd "$(dirname $0)"
pkill -9 -u sandbox
./repair-permissions.sh && sudo -u webserver ruby webserver.rb stacked-crooked.com 80
