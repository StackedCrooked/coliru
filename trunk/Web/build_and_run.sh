#!/bin/bash
export CHROOT="/var/chroot"

rm -rf "${CHROOT}/tmp/*"
set -e
ulimit -f 1000
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." 1>&2 ; exit 1; }
cp compile.sh main.cpp "${CHROOT}/tmp/"

# Run the chroot
{ { sleep 10 && echo "Timeout!" && { pkill -9 -u sandbox >/dev/null 2>&1  ; } && exit 1 ; } & } && { trap "kill $! >/dev/null 2>&1" INT ERR EXIT; ./chroot.sh ; exit 0 ; }

