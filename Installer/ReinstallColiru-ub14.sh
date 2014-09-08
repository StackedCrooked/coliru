#!/bin/bash

# Two goals of this script are:
#  (1) Install Coliru
#  (2) Repair Coliru 
#
# When running this script for a second time then it 
# should only reinstall the parts that are missing or
# damaged.


set -e
set -x


# Remote setuid root from programs
#chmod -s /bin/fusermount
chmod -s /usr/bin/newgrp
chmod -s /usr/bin/gpasswd
chmod -s /usr/bin/mtr
chmod -s /bin/ping
#chmod -s /usr/bin/sudoedit
chmod -s /usr/bin/at
#chmod -s /usr/bin/chsh
#chmod -s /usr/bin/chfn
#chmod -s /usr/bin/sudo
#chmod -s /usr/bin/passwd
#chmod -s /usr/sbin/uuidd
#chmod -s /usr/sbin/pppd




# Install g++-4.8 and related things.
# TODO: This is a mess and needs to be cleaned up.
type 'g++-4.8' || { \
	apt-get install -y python-software-properties
	add-apt-repository ppa:ubuntu-toolchain-r/test
	apt-get update
	apt-get upgrade
	apt-get install g++-4.7 g++-4.8 libstdc++-4.8-dev
    ln -fs /usr/bin/g++-4.8 /usr/bin/g++
}



# Install dchroot and debootstrap
# TODO: I don't remember if this was needed to run coliru.
#       This should either be cleaned up or moved a better place.
apt-get install -y dchroot debootstrap


# Install ruby and rubygems.
# TODO: This is a mess.
apt-get install -y libcap2-bin ruby-dev lsof rsync subversion
gem install sinatra shotgun popen4 json sinatra-cross_origin --no-ri --no-rdoc


# Enable required capabilities for the webserver user.

# Allow ruby to bind to port 80
setcap 'cap_net_bind_service=+ep' /usr/bin/ruby1.9.1 || true

# Allow bash and chroot to run the chroot command
setcap 'cap_sys_chroot=+ep' /bin/bash
setcap 'cap_sys_chroot=+ep' /usr/sbin/chroot


# Allow kill and pkill to kill without root priviliges.
setcap 'cap_kill=+ep' /bin/kill
setcap 'cap_kill=+ep' /usr/bin/pgrep


# Create users and groups.
# TODO: The user ids should not be hardcoded because that
#       makes it harder to install Coliru on other machines.
groupadd -g 2000 coliru || echo "Group coliru already exists. Continuing."
useradd -g coliru -u 2000 coliru-launcher || echo "User coliru-launcher already exists. Continuing."
useradd -g coliru -u 2001 webserver || echo "User webserver already exists. Continuing."
useradd -g coliru -u 2002 sandbox || echo "User sandbox already exists. Continuing."


# SECURITY SETTINGS

# sandbox user can not access the network
iptables -A OUTPUT -m owner --uid-owner 2002 -j DROP

# Set the securit limites for the webserver and sandbox users.
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


# Disable the annoying Whoopsie report crashes and stop the whoopsie service
sed -i "s/\(report_crashes=\).*/\1false/" /etc/default/whoopsie || true
sudo service whoopsie stop || echo "whoopsie was already stopped."


# Set up the chroot directory
./RebuildChroot.sh

echo "TODO: Add this line to visudo"
echo " * Add this line to visudo"
echo "   webserver  ALL=(sandbox) NOPASSWD: ALL"
echo " * Set COLIRU_URL and COLIRU_PORT"


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
