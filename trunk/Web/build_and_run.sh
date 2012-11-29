#!/bin/bash
if [ -z "${CHROOT}" ] ; then
    echo "CHROOT environment variable is not set. Exiting." 1>&2
fi

ulimit -f 1000
rm -rf "${CHROOT}/*"
set -e
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." >2 ; exit 1; }
cp compile.sh main.cpp "${CHROOT}/"

# Run the chroot
{ { sleep 10 && echo "Timeout!" && { pkill -9 -u sandbox >/dev/null 2>&1  ; } && exit 1 ; } & } && { trap "kill $! >/dev/null 2>&1" INT ERR EXIT; ./chroot.sh ; exit 0 ; }

