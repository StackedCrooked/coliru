#!/bin/bash
set -e
set -x
CHROOT="/var/chroot"

if [ $(whoami) != "root" ] ; then
	echo "Installation requires root permissions. Exiting." 1>&2
	exit 1
fi

if [ -d ${CHROOT} ] ; then
	echo "Warning: ${CHROOT} already exists." 1>&2 || true
fi


apt-get install python-software-properties
add-apt-repository ppa:ubuntu-toolchain-r/test
apt-get update
apt-get upgrade
apt-get install g++-4.7



apt-get install -y libcap2-bin ruby rubygems lsof
gem install mongrel popen4


setcap 'cap_net_bind_service=+ep' /usr/bin/ruby1.8
setcap 'cap_sys_chroot=+ep' /bin/bash
setcap 'cap_kill=+ep' /bin/kill
setcap 'cap_kill=+ep' /usr/bin/pkill


groupadd -g 2000 coliru
useradd -g coliru -u 2001 webserver
useradd -g coliru -u 2002 sandbox


LIMITS_ALREADY_SET=$(cat /etc/security/limits.conf | grep COLIRU | wc -l)
echo "LIMITS_ALREADY_SET: ${LIMITS_ALREADY_SET}"
if [ $LIMITS_ALREADY_SET -ne 0 ] ; then
    echo "
    # BEGIN COLIRU SETTINGS
    webserver soft nproc 20
    webserver hard nproc 20

    sandbox sort nproc 10
    sandbox hard nproc 10

    sandbox hard cpu   1
    sandbox soft cpu   1
    # END COLIRU SETTINGS
    " >> /etc/security/limits.conf
fi


mkdir -p ${CHROOT}
rsync -avzl /bin /usr /lib /lib64 ${CHROOT}/
chmod -R o-r ${CHROOT}/
mkdir -p ${CHROOT}/tmp
chown -R sandbox:coliru ${CHROOT}/tmp
