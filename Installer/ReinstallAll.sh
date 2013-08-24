#!/bin/bash
set -e
set -x

./RebuildChroot.sh

type 'g++-4.8' || { \
	apt-get install -y python-software-properties
	add-apt-repository ppa:ubuntu-toolchain-r/test
	apt-get update
	apt-get upgrade
	apt-get install g++-4.7 g++-4.8 libstdc++-4.8-dev
    ln -fs /usr/bin/g++-4.8 /usr/bin/g++
}

apt-get install -y dchroot debootstrap


apt-get install -y libcap2-bin ruby-dev rubygems lsof rsync subversion
gem install sinatra shotgun popen4 json sinatra-cross_origin --no-ri --no-rdoc


# Allow ruby to bind to port 80
setcap 'cap_net_bind_service=+ep' /usr/bin/ruby1.8 || true

# Allow bash and chroot to run the chroot command
setcap 'cap_sys_chroot=+ep' /bin/bash
setcap 'cap_sys_chroot=+ep' /usr/sbin/chroot


# Allow kill and pkill to kill without root priviliges.
setcap 'cap_kill=+ep' /bin/kill
setcap 'cap_kill=+ep' /usr/bin/pgrep


# Create users and groups.
groupadd -g 2000 coliru || echo "Group coliru already exists. Continuing."
useradd -g coliru -u 2000 coliru-launcher || echo "User coliru-launcher already exists. Continuing."
useradd -g coliru -u 2001 webserver || echo "User webserver already exists. Continuing."
useradd -g coliru -u 2002 sandbox || echo "User sandbox already exists. Continuing."


LIMITS_ALREADY_SET=$(cat /etc/security/limits.conf | grep COLIRU | wc -l)
echo "LIMITS_ALREADY_SET: ${LIMITS_ALREADY_SET}"
if [ "$LIMITS_ALREADY_SET" == "0" ] ; then
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


# Set report_crashes=false in /etc/default/whoopsie
sed -i "s/\(report_crashes=\).*/\1false/" /etc/default/whoopsie

# And stop the whoopsie service
sudo service whoopsie stop || true


# TODO: Install wheels
#apt-get install mercurial
#hg clone https://bitbucket.org/martinhofernandes/wheels

 # TODO: Install locales
 #1984  for i in $(echo en_US.utf8 ja_JP.utf8 sv_SE.utf8 ru_RU.utf8 vi_VN.utf8) ; do locale-gen $i ; locale-gen ${i}.UTF8 ; done ; update-locale
 #1985  locale-gen vi_VN.UTF8
 #1986  echo 'for i in $(echo en_US.utf8 ja_JP.utf8 sv_SE.utf8 ru_RU.utf8 vi_VN.utf8) ; do locale-gen $i ; locale-gen ${i}.UTF8 ; done ; update-locale' | perl -pe 's,\.utf8,,g'
 #1987  for i in $(echo en_US ja_JP sv_SE ru_RU vi_VN) ; do locale-gen $i.utf8 ; locale-gen ${i}.UTF8 ; done ; update-locale
 #1988  locale-gen vi.utf8
 #1989  locale-gen vi.UTF8
 #1990  locale-gen vi_VN.utf8
 #1991  locale-gen vi_VN.UTF8
 #1992  locale-update
 #1993  update-locale
 #1994  locale-gen vi_VN
 #1995  locale-gen vi_VN.utf8
 #1996* locale-gen cs_CZ.utf8
 #1997  update-locale
 #1998  locale-gen vi_VN.utf8
 #1999  locale-gen cs_CZ.utf8
 #2000  locale-gen cs_CZ.UTF8
 #2001  locale-gen zh_CN.gb18030
 #2002  update-locale
 #2003  locale-gen zh_CN.gb18030
 #2004  update-locale
 #2005  history | grep locale
 #2006  history | grep locale >>~/coliru/Installer/Install.sh 
