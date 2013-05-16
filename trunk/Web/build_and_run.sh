#!/bin/bash
export CHROOT="/var/chroot"
echo "now INPUT_FILES_DIR is ${INPUT_FILES_DIR} " >> webserver.log
echo "now INPUT_FILES_DIR constains $(ls ${INPUT_FILES_DIR}) " >> webserver.log

TIMEOUT=$(cat timeout.txt 2>/dev/null || echo 20)
if [ "${TIMEOUT}" != "" ] ; then
    COLIRU_TIMEOUT=${TIMEOUT}
else
    COLIRU_TIMEOUT=${COLIRU_DEFAULT_TIMEOUT}
fi


CHROOT_TARGET_DIRNAME=$(basename ${INPUT_FILES_DIR})
chmod 755 ${INPUT_FILES_DIR}/cmd.sh
mv ${INPUT_FILES_DIR} ${CHROOT}/tmp/


#
# Insert set -x and ulimit
#
HLP=${CHROOT}/tmp/$(basename ${INPUT_FILES_DIR})
CMD=${HLP}/cmd.sh
mv ${CMD} ${CMD}_
echo 'ulimit -u 20' >> ${CMD}
echo 'set -x' >> ${CMD}
cat ${CMD}_ >> ${CMD}
rm ${CMD}_
chmod a+rx ${CMD}

export CHROOT_TARGET_PATH=${CHROOT}/tmp/${CHROOT_TARGET_DIRNAME}
chmod -R a+w ${CHROOT}/tmp/${CHROOT_TARGET_DIRNAME}

cp compile.sh /var/chroot/tmp/$(basename ${CHROOT_TARGET_DIRNAME}).sh
./chroot.sh
