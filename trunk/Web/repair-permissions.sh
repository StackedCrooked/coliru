#!/bin/bash
set -x
echo "$0 executed by $(whoami)"

touch webserver.log ; chown a+rw webserver.log
chown webserver:coliru .
chown webserver:coliru ${COLIRU_ARCHIVE}
chmod a+rw .

find /var/chroot/tmp -type f | xargs -I {} rm -f {} || sudo -u sandbox find /var/chroot/tmp -type f | xargs -I {} rm -f {}
chmod -R a+rw /var/chroot/tmp >/dev/null 2>&1 || sudo -u sandbox chmod -R a+rw /var/chroot/tmp >/dev/null 2>&1

echo "Owner of /var/chroot/tmp is $(ls -alt /var/chroot/tmp | head -n2 | tail -n1)"
rm -rf /var/chroot/tmp
mkdir -p /var/chroot/tmp
chown -R webserver:coliru /var/chroot/tmp
chmod a+rw /var/chroot/tmp

for file in "output main.cpp cmd.sh /var/chroot/tmp/main.cpp /var/chroot/tmp/compile.sh" ; do
  touch $file && chown webserver:coliru $file
done
