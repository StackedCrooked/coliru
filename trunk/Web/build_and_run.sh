#!/bin/bash
export CHROOT="/var/chroot"

rm -rf "${CHROOT}/tmp/*"
set -e
ulimit -f 10000
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." 1>&2 ; exit 1; }

chmod 755 cmd.sh
cp compile.sh cmd.sh main.cpp "${CHROOT}/tmp/"
chmod 755 "${CHROOT}/tmp/compile.sh"

./chroot.sh
