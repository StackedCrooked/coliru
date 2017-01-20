#!/bin/bash
if [ "$(whoami)" != "root" ] ; then
    echo "$(basename $0) must be run as root." 1>&2
    exit 1
fi


chmod a+rw /var/log/syslog
source coliru_env.source

# The webserver needs write access to the archive.
# Only occasionally these are run because they are very resource consuming
#export counter="$(./fvar_inc.sh repair-permissions-counter)"
#echo "counter=$counter"
#chown -R webserver:coliru ${COLIRU_ARCHIVE2} & disown 
#chown -R webserver:coliru ${COLIRU_COMPILE_ARCHIVE} & disown 

chmod a+rw .

# Cleanup temporary files
rm -rf /tmp/coliru/*
chown -R webserver:coliru /tmp


# Cleanup /var/chroot/tmp and make accessible for coliru
rm -rf /var/chroot/tmp/*
mkdir -p /var/chroot/tmp
chown -R webserver:coliru /var/chroot/tmp
chmod -R a+rw /var/chroot/tmp

# Make certain files writeable for the webserver.
for file in $(echo new-feedback.txt feedback.txt timeout.txt ../Archive2.log Archive2.log) ; do
  [ -f ${file} ] || echo >${file}
  chown webserver:coliru ${file}
done

(cd ../Installer && ./RebuildChroot.sh)
