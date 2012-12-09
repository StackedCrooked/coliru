#!/bin/bash

chown -R webserver:coliru .
chmod -R a+rw .

rm -rf /var/chroot/tmp
mkdir -p /var/chroot/tmp
chown -R sandbox:coliru /var/chroot/tmp

touch ./output
chown -R webserver:coliru ./output

touch ./main.cpp
chown -R webserver:coliru ./main.cpp

touch /var/chroot/tmp/main.cpp
chown -R webserver:coliru /var/chroot/tmp/main.cpp 

touch /var/chroot/tmp/compile.sh 
chown -R webserver:coliru /var/chroot/tmp/compile.sh 

chmod -R a+r /var/chroot/tmp
chmod -R g+w /var/chroot/tmp
