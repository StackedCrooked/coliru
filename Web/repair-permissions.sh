#!/bin/bash
echo "$0 executed by $(whoami)"
source coliru_env.source

touch feedback.txt ; chown webserver:coliru feedback.txt ; chmod +w feedback.txt
chown webserver:coliru .
chown webserver:coliru ${COLIRU_ARCHIVE}
chmod a+rw .

#find /var/chroot/tmp -type f | xargs -I {} rm -f {} || sudo -u sandbox find /var/chroot/tmp -type f | xargs -I {} rm -f {}
#chown -R sandbox:coliru /var/chroot & disown
chmod -R a+rw /var/chroot/tmp >/dev/null 2>&1 || sudo -u sandbox chmod -R a+rw /var/chroot/tmp >/dev/null 2>&1

echo "Owner of /var/chroot/tmp is $(ls -alt /var/chroot/tmp | head -n2 | tail -n1)"
rm -rf /var/chroot/tmp
mkdir -p /var/chroot/tmp
chown -R webserver:coliru /var/chroot/tmp
chmod -R a+rw /var/chroot/tmp

# Cleanup /dev
mkdir -p /var/chroot/dev
touch /var/chroot/dev/null

for file in "output main.cpp cmd.sh" ; do
  touch $file && chown webserver:coliru $file
done


# Mount the chroot directories
for dir in $(echo /usr /bin /lib /lib64) ; do
    { mkdir -p ${CHROOT}${dir} && mount --bind ${dir} ${CHROOT}${dir} && mount -o remount,ro ${CHROOT}${dir} ; } || true
done

# Mount the Archive
{ mkdir -p ${CHROOT}/Archive && mount --bind ../Archive ${CHROOT}/Archive && mount -o remount,ro ${CHROOT}/Archive ; } || true
