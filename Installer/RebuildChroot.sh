#!/bin/bash
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

archive="$(echo $(dirname $0)/../Archive)"
mount_dir_into_chroot ${archive} /usr /bin /var /lib /lib64 /etc/alternatives


# Add /dev/null and /dev/random to the chroot
#
# Based on the instructions found here:
#  http://www.losurs.org/docs/howto/Chroot-BIND-2.html
mkdir -p /var/chroot/dev

file /var/chroot/dev/null || {
    mknod /var/chroot/dev/null c 1 3  
    chmod 666 /var/chroot/dev/null
}

file /var/chroot/dev/random || {
    mknod /var/chroot/dev/random c 1 8
    chmod 666 /var/chroot/dev/random
}


# Create the tmp folder and set the
# permissions for the sandbox users.
mkdir -p ${CHROOT}/tmp
chown -R sandbox:coliru ${CHROOT}/tmp

