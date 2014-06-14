#!/bin/bash

# This script sets up the choot for running user programs.
# Running the script for a second time will repair the chroot (if needed).


set -x
set -e

if [ $(whoami) != "root" ] ; then
	echo "Installation requires root permissions. Exiting." 1>&2
	exit 1
fi

CHROOT="/var/chroot"

mount_dir_into_chroot() {
    for dir in $@ ; do
        mkdir -p ${CHROOT}${dir}
        mount --bind ${dir} ${CHROOT}${dir}
        mount -o remount,ro ${CHROOT}${dir}
    done
}

archive="/Archive"
archive2="/Archive2"
mount_dir_into_chroot ${archive} ${archive2} /usr /bin /var /lib /lib64 /etc/alternatives

# Add manpath.config to chroot
cp /etc/manpath.config ${CHROOT}/etc/manpath.config
chown sandbox:coliru ${CHROOT}/etc/manpath.config


# Add /dev/null and /dev/random to the chroot
#
# Based on the instructions found here:
#  http://www.losurs.org/docs/howto/Chroot-BIND-2.html
mkdir -p /var/chroot/dev/fd

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
chown -R sandbox:coliru ${CHROOT}/dev

