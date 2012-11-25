#!/bin/bash
if [ "$(whoami)" != "sandbox" ]; then
	echo "For security reasons this script must be run by a user named \"webserver\"."
	exit 1
fi
NPROC_LIMIT=`ulimit -a 2>&1 | grep "\-u" | awk '{print $5}'`
[ ${NPROC_LIMIT} -lt 20 ] || { echo "NPROC limit is too high: ${NPROC_LIMIT}. Exiting." >&2 ; exit 1 ; }
ulimit -t 1
ulimit -n 20

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
[ -f main.cpp ] || { echo "No main.cpp found in ${DIR}." >&2 ; echo "Exiting." >&2 ; exit 1 ; }
cp main.cpp /var/chroot/home/lol/main.cpp
echo "cd /home/lol && bash main.cpp" >/var/chroot/home/lol/build.sh
chroot /var/chroot bash /home/lol/build.sh

