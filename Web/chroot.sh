#!/bin/bash
export CHROOT=/var/chroot
sudo -u sandbox chroot "${CHROOT}" ${1}/compile.sh ${1}
