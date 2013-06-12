#!/bin/bash
ulimit -f 10000

PROCESS_COUNT=16
TIMEOUT=$(cat timeout.txt 2>/dev/null || echo 20)
if [ "${TIMEOUT}" != "" ] ; then
    COLIRU_TIMEOUT=${TIMEOUT}
else
    COLIRU_TIMEOUT=${COLIRU_DEFAULT_TIMEOUT}
fi


COLIRU_JOBID=$(basename ${INPUT_FILES_DIR})
mv ${INPUT_FILES_DIR} ${CHROOT}/tmp/
export CHROOT_TARGET_PATH=${CHROOT}/tmp/${COLIRU_JOBID}


#
# Insert set -x and ulimit
#
CMD_FILE=${CHROOT_TARGET_PATH}/cmd.sh
mv ${CMD_FILE} ${CMD_FILE}_
echo '#!/bin/bash' >> ${CMD_FILE}
echo "ulimit -u ${PROCESS_COUNT}" >> ${CMD_FILE}
echo "ulimit -t ${TIMEOUT}" >> ${CMD_FILE}
echo "ulimit -f 10" >> ${CMD_FILE}
echo 'cd $(dirname $0)' >> ${CMD_FILE}
echo 'export LD_LIBRARY_PATH="/usr/local/lib:${LD_LIBRARY_PATH}"' >> ${CMD_FILE}
echo 'set -x' >> ${CMD_FILE}
cat ${CMD_FILE}_ >> ${CMD_FILE}
rm ${CMD_FILE}_
chmod a+rx ${CMD_FILE}

chmod -R a+w ${CHROOT_TARGET_PATH}

setsid sudo -u sandbox chroot "${CHROOT}" /tmp/${COLIRU_JOBID}/cmd.sh
