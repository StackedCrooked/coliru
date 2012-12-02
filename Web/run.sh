#!/bin/bash
cd "$(dirname $0)"
pkill -9 -u webserver

mkdir -p /var/chroot/tmp
chown -R sandbox:coliru ./output

touch ./output
chown -R webserver:coliru ./output

touch ./main.cpp
chown -R webserver:coliru ./main.cpp

touch /var/chroot/tmp/main.cpp
chown -R webserver:coliru /var/chroot/tmp/main.cpp 

touch /var/chroot/tmp/compile.sh 
chown -R webserver:coliru /var/chroot/tmp/compile.sh 

sudo -u webserver ruby webserver.rb stacked-crooked.com 80
