#!/bin/bash
if [ "$(whoami)" != "root" ] ; then
    echo "$(basename $0) must be run as root." 1>&2
    exit 1
fi

chmod a+rw /var/log/syslog
source coliru_env.source

chown -R webserver:coliru ..
chmod a+rw .


# Cleanup /var/chroot/tmp and make accessible for coliru
rm -rf /var/chroot/tmp
mkdir -p /var/chroot/tmp
chown -R webserver:coliru /var/chroot/tmp
chmod -R a+rw /var/chroot/tmp

# Make certain files writeable for the webserver.
for file in "feedback.txt timeout.txt output main.cpp cmd.sh timestamp.txt" ; do
  touch $file && chown webserver:coliru $file
done


# Mount the chroot directories
for dir in $(echo /usr /bin /lib /lib64) ; do
    { mkdir -p ${CHROOT}${dir} && mount --bind ${dir} ${CHROOT}${dir} && mount -o remount,ro ${CHROOT}${dir} ; } || true
done

# Mount the Archive
{ mkdir -p ${CHROOT}/Archive && mount --bind ../Archive ${CHROOT}/Archive && mount -o remount,ro ${CHROOT}/Archive ; } || true
