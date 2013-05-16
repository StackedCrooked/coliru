#!/bin/bash
export CHROOT="/var/chroot"
echo "now TMP_DIR is ${TMP_DIR} " >> webserver.log
echo "now TMP_DIR constains $(ls ${TMP_DIR}) " >> webserver.log

TIMEOUT=$(cat timeout.txt 2>/dev/null || echo 20)
if [ "${TIMEOUT}" != "" ] ; then
    COLIRU_TIMEOUT=${TIMEOUT}
else
    COLIRU_TIMEOUT=${COLIRU_DEFAULT_TIMEOUT}
fi


#[ -d ${CHROOT}/${TMP_DIR} ] && { echo "The temp directory already exists: ${TMP_DIR}." 1>&2 ; exit 1 ; }
#sudo -u sandbox chroot ${CHROOT} mkdir -p ${TMP_DIR}
DIR=$(basename ${TMP_DIR})
chmod 755 ${TMP_DIR}/cmd.sh
mv ${TMP_DIR} ${CHROOT}/tmp/


#
# Insert set -x and ulimit
#
HLP=${CHROOT}/tmp/$(basename ${TMP_DIR})
CMD=${HLP}/cmd.sh
mv ${CMD} ${CMD}_
echo 'set -x' >> ${CMD}
echo 'ulimit -u 20' >> ${CMD}
cat ${CMD}_ >> ${CMD}
rm ${CMD}_
chmod a+rx ${CMD}

export DST=${CHROOT}/tmp/${DIR}
chmod -R a+w ${CHROOT}/tmp/${DIR}

cp compile.sh /var/chroot/tmp/$(basename ${DIR}).sh
./chroot.sh
