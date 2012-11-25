#!/bin/bash
set -x
set -e
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." >2 ; exit 1; }
cp compile.sh main.cpp /var/chroot/tmp

# Run the chroot
SANDBOX_UID=`id sandbox | cut -d ' ' -f1 | cut -d '=' -f2 | cut -d '(' -f1`
SANDBOX_GID=`id sandbox | cut -d ' ' -f2 | cut -d '=' -f2 | cut -d '(' -f1`
chroot --userspec=${SANDBOX_UID}:${SANDBOX_GID} /var/chroot /tmp/compile.sh
