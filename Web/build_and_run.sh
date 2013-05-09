#!/bin/bash
export CHROOT="/var/chroot"

TIMEOUT=$(cat timeout.txt 2>/dev/null || echo 20)
if [ "${TIMEOUT}" != "" ] ; then
    COLIRU_TIMEOUT=${TIMEOUT}
else
    COLIRU_TIMEOUT=${COLIRU_DEFAULT_TIMEOUT}
fi


rm -rf "${CHROOT}/tmp/*"
set -e
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." 1>&2 ; exit 1; }

cp cmd.sh main.cpp "${CHROOT}/tmp/"

# copy cmd.sh to chroot but prepend 'set -x' first. And make it executable as well.
echo 'set -x' >  "${CHROOT}/tmp/cmd.sh" && cat cmd.sh | sed -e "s/TIMEOUT/${COLIRU_TIMEOUT}/" >> "${CHROOT}/tmp/cmd.sh" && chmod 755 "${CHROOT}/tmp/cmd.sh"

# copy compile.sh to chroot but replace TIMEOUT with actual timeout. And also make it executable.
cat compile.sh | sed -e "s/TIMEOUT/${COLIRU_TIMEOUT}/" > "${CHROOT}/tmp/compile.sh" && chmod 755 "${CHROOT}/tmp/compile.sh"

./chroot.sh
