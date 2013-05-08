#!/bin/bash
export CHROOT=/var/chroot
export COLIRU_TIMEOUT=$(cat timeout.txt || echo 20)

sudo -u sandbox chroot "${CHROOT}" /tmp/compile.sh
