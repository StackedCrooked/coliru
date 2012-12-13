#!/bin/bash
export CHROOT="/var/chroot"

rm -rf "${CHROOT}/tmp/*"
set -e
ulimit -f 2000
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." 1>&2 ; exit 1; }
cp compile.sh main.cpp "${CHROOT}/tmp/"
chmod 755 "${CHROOT}/tmp/compile.sh"

./chroot.sh
