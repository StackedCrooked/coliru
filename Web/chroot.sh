#!/bin/bash
if [ -z "${CHROOT}" ] ; then
    echo "CHROOT environment variable is not set. Exiting." 1>&2
fi
sudo -u sandbox chroot "${CHROOT}" /tmp/compile.sh
