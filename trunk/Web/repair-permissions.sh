#!/bin/bash
if [ "$(whoami)" != "root" ] ; then
    echo "$(basename $0) must be run as root." 1>&2
    exit 1
fi

chmod a+rw /var/log/syslog
source coliru_env.source

chown webserver:coliru ${COLIRU_ARCHIVE2}
#chown -R webserver:coliru .. & disown
chmod a+rw .


# Cleanup /var/chroot/tmp and make accessible for coliru
mkdir -p /var/chroot/tmp
chown -R webserver:coliru /var/chroot/tmp & disown
chmod -R a+rw /var/chroot/tmp

# Make certain files writeable for the webserver.
for file in "feedback.txt timeout.txt output main.cpp cmd.sh timestamp.txt" ; do
  touch $file && chown webserver:coliru $file
done
