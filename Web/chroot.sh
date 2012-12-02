#!/bin/bash
export CHROOT=/var/chroot
sudo -u sandbox chroot "${CHROOT}" /tmp/compile.sh
