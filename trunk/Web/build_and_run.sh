#!/bin/bash
set -e
export CHROOT="/var/chroot"

TIMEOUT=$(cat timeout.txt 2>/dev/null || echo 20)
if [ "${TIMEOUT}" != "" ] ; then
    COLIRU_TIMEOUT=${TIMEOUT}
else
    COLIRU_TIMEOUT=${COLIRU_DEFAULT_TIMEOUT}
fi


TMP_DIR="/tmp/$(date '+%s')"
[ ! -d ${TMP_DIR} ] || { echo "The temp directory already exists: ${TMP_DIR}." 1>&2 ; exit 1 ; }
#sudo -u sandbox chroot ${CHROOT} mkdir -p ${TMP_DIR}
mkdir -p ${CHROOT}/${TMP_DIR}
chmod -R a+w ${CHROOT}/${TMP_DIR}

rm -rf "${CHROOT}/${TMP_DIR}/*"
set -e
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." 1>&2 ; exit 1; }

mv main.cpp "${CHROOT}/${TMP_DIR}/"

# copy cmd.sh to chroot but prepend 'set -x' first. And make it executable as well.
echo 'set -x' >  "${CHROOT}/${TMP_DIR}/cmd.sh" && cat cmd.sh | sed -e "s/TIMEOUT/${COLIRU_TIMEOUT}/" >> "${CHROOT}/${TMP_DIR}/cmd.sh" && chmod 755 "${CHROOT}/${TMP_DIR}/cmd.sh"

# copy compile.sh to chroot but replace TIMEOUT with actual timeout. And also make it executable.
cat compile.sh | sed -e "s/TIMEOUT/${COLIRU_TIMEOUT}/" > "${CHROOT}/${TMP_DIR}/compile.sh" && chmod 755 "${CHROOT}/${TMP_DIR}/compile.sh"

./chroot.sh ${TMP_DIR}
