#!/bin/bash
ulimit -f 100
set -e
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." >2 ; exit 1; }
cp compile.sh main.cpp /var/chroot/tmp

# Run the chroot
{ { sleep 5 && echo "Timeout!" && pkill -9 -u sandbox && exit 1 ; } & } && { trap "kill $!" INT ERR EXIT; ./chroot.sh ; exit 0 ; }
