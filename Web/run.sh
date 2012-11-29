#!/bin/bash
pkill -9 -u webserver
chown -R webserver:coliru /var/chroot/tmp/main.cpp 
chown -R webserver:coliru /var/chroot/tmp/compile.sh 
sudo -u webserver ruby webserver.rb stacked-crooked.com 80
