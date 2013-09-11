#!/bin/bash
if [ "$(whoami)" != "root" ] ; then
    echo "$(basename $0) must be run as root." 1>&2
    exit 1
fi


chmod a+rw /var/log/syslog
source coliru_env.source

# The webserver needs write access to the archive.
chown -R webserver:coliru ${COLIRU_ARCHIVE2} & disown
chmod a+rw .


# Cleanup temporary files
rm -rf /tmp/coliru/* & disown


# Cleanup /var/chroot/tmp and make accessible for coliru
rm -rf /var/chroot/tmp/* & disown
mkdir -p /var/chroot/tmp
chown -R webserver:coliru /var/chroot/tmp & disown
chmod -R a+rw /var/chroot/tmp

# Make certain files writeable for the webserver.
for file in "feedback.txt timeout.txt output main.cpp cmd.sh timestamp" ; do
  touch $file && chown webserver:coliru $file
done

(cd ../Installer && ./RebuildChroot.sh)
