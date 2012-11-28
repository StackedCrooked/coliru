#!/bin/bash
if [ "$(uname)" == "Darwin" ] ; then 
    ID="$(md5 main.cpp | cut -d '=' -f 2 | sed -e 's/ //g')"
else
    ID="$(md5sum main.cpp | cut -d ' ' -f 1)"
fi

if [ -f "Archive/${ID}/output" ] ; then
    cat "Archive/${ID}/output"
    exit
fi


if [ "$(uname)" == "Darwin" ] ; then 
    g++ -std=c++0x -o test -pthread main.cpp && ./test
    exit 0
fi
ulimit -f 100
set -e
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." >2 ; exit 1; }
cp compile.sh main.cpp /var/chroot/tmp

# Run the chroot
{ { sleep 10 && echo "Timeout!" && { pkill -9 -u sandbox >/dev/null 2>&1  ; } && exit 1 ; } & } && { trap "kill $! >/dev/null 2>&1" INT ERR EXIT; ./chroot.sh ; exit 0 ; }
