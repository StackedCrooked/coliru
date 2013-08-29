apt-get install lxc debootstrap vlan bridge-utils python-software-properties screen 
mkdir -p /lxc ; cd /lxc 
debootstrap --variant=minbase --arch amd64 precise rootfs.ubuntu
