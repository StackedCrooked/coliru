#!/bin/bash

# This script sets up the choot for running user programs.
# Running the script for a second time will repair the chroot (if needed).


set -x
set -e

CHROOT="/var/chroot"
ARCHIVE="/Archive"
ARCHIVE2="/Archive2"

mount_dir_into_chroot() {
    for dir in $@ ; do
        mkdir -p ${CHROOT}${dir}
        mount --bind ${dir} ${CHROOT}${dir}
        mount -o remount,ro,bind ${CHROOT}${dir}
    done
}



mount_dir_into_chroot /etc/alternatives 
mount_dir_into_chroot /lib64
mount_dir_into_chroot /lib
mount_dir_into_chroot /var
mount_dir_into_chroot /bin
mount_dir_into_chroot /usr
mount_dir_into_chroot /proc
mount_dir_into_chroot ${ARCHIVE2}
mount_dir_into_chroot ${ARCHIVE}

# /dev is special
mkdir -p "${CHROOT}/dev"

# Add /dev/null and /dev/random to the chroot
#
# Based on the instructions found here:
#  http://www.losurs.org/docs/howto/Chroot-BIND-2.html
mkdir -p /var/chroot/dev

file /var/chroot/dev/null || {
    mknod /var/chroot/dev/null c 1 3  
    chmod 666 /var/chroot/dev/null
}


file /var/chroot/dev/urandom || {
    mknod /var/chroot/dev/urandom c 1 9
    chmod 666 /var/chroot/dev/urandom
}


file /var/chroot/dev/random || {
    mknod /var/chroot/dev/random c 1 8
    chmod 666 /var/chroot/dev/random
}


# Create the tmp folder and set the
# permissions for the sandbox users.
mkdir -p ${CHROOT}/tmp
chown -R sandbox:coliru ${CHROOT}/tmp

