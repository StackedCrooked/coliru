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

mkdir -p ${CHROOT}

if [ ! type g++-4.8 ] ; then
	apt-get install -y python-software-properties
	add-apt-repository ppa:ubuntu-toolchain-r/test
	apt-get update
	apt-get upgrade
	apt-get install g++-4.7 g++-4.8 libstdc++-4.8-dev
fi

apt-get install -y dchroot debootstrap

for dir in $(echo /usr /bin /lib /lib64) ; do
    mount --bind ${dir} ${CHROOT}${dir}
    mount -o remount,ro ${CHROOT}${dir}
done


apt-get install -y libcap2-bin ruby-dev rubygems lsof rsync subversion
gem install sinatra shotgun popen4


for ruby in `ls /usr/bin/ruby*` ; do
    setcap 'cap_net_bind_service=+ep' $ruby || true
done

setcap 'cap_sys_chroot=+ep' /bin/bash
setcap 'cap_sys_chroot=+ep' /usr/sbin/chroot
setcap 'cap_kill=+ep' /bin/kill
setcap 'cap_kill=+ep' /usr/bin/pgrep


groupadd -g 2000 coliru || echo "Group coliru already exists. Continuing."
useradd -g coliru -u 2000 coliru-launcher || echo "User coliru-launcher already exists. Continuing."
useradd -g coliru -u 2001 webserver || echo "User webserver already exists. Continuing."
useradd -g coliru -u 2002 sandbox || echo "User sandbox already exists. Continuing."


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


mkdir -p ${CHROOT}/tmp
chown -R sandbox:coliru ${CHROOT}/tmp



# TODO: Install wheels
#apt-get install mercurial
#hg clone https://bitbucket.org/martinhofernandes/wheels

