#!/bin/bash
if [ "$(uname)" == "Darwin" ] ; then 
    g++ -std=c++0x -o test -pthread main.cpp && ./test
    exit 0
fi
ulimit -f 100
set -e
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." >2 ; exit 1; }
cp compile.sh main.cpp /var/chroot/tmp

# Run the chroot
{ { sleep 5 && echo "Timeout!" && { pkill -9 -u sandbox >/dev/null 2>&1  ; } && exit 1 ; } & } && { trap "kill $! >/dev/null 2>&1" INT ERR EXIT; ./chroot.sh ; exit 0 ; }
