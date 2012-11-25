#!/bin/bash
set -e
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." >2 ; exit 1; }
cp compile.sh main.cpp /var/chroot/tmp

# Run the chroot
sudo -u sandbox chroot /var/chroot /tmp/compile.sh
