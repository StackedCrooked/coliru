#!/bin/bash
export CHROOT=/var/chroot
ID=$(basename ${DST})
sudo -u sandbox chroot "${CHROOT}" /tmp/${ID}.sh /tmp/${ID}
