#!/bin/bash
export CHROOT="/var/chroot"

TIMEOUT=$(cat timeout.txt 2>/dev/null || echo 20)
if [ "${TIMEOUT}" != "" ] ; then
    COLIRU_TIMEOUT=${TIMEOUT}
else
    COLIRU_TIMEOUT=${COLIRU_DEFAULT_TIMEOUT}
fi


[ ! -d ${CHROOT}/${TMP_DIR} ] || { echo "The temp directory already exists: ${TMP_DIR}." 1>&2 ; exit 1 ; }
#sudo -u sandbox chroot ${CHROOT} mkdir -p ${TMP_DIR}
DIR=$(basename ${TMP_DIR})
chmod 755 ${TMP_DIR}/cmd.sh
mv ${TMP_DIR} ${CHROOT}/tmp/
export DST=${CHROOT}/tmp/${DIR}
chmod -R a+w ${CHROOT}/tmp/${DIR}

cp compile.sh /var/chroot/tmp/$(basename ${DIR}).sh
./chroot.sh
