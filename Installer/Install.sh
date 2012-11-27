#!/bin/bash
set -e
CHROOT="/var/chroot/"

if [ $(whoami) != "root" ] ; then
	echo "Installation requires root permissions. Exiting." 1>&2
	exit 1
fi

if [ -d ${CHROOT} ] ; then
	echo "Warning: ${CHROOT} already exists." 1>&2 || true
fi

mkdir -p ${CHROOT}
rsync -avzl /bin /usr /lib /lib64 ${CHROOT}

