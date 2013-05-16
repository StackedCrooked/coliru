#!/bin/bash
export CHROOT=/var/chroot
ID=$(basename ${CHROOT_TARGET_PATH})
sudo -u sandbox chroot "${CHROOT}" /tmp/${ID}/cmd.sh
