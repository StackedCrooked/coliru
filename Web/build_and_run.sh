#!/bin/bash
source coliru_env.source
ulimit -f 10000

TIMEOUT=$(cat timeout.txt 2>/dev/null || echo 20)
if [ "${TIMEOUT}" != "" ] ; then
    COLIRU_TIMEOUT=${TIMEOUT}
else
    COLIRU_TIMEOUT=${COLIRU_DEFAULT_TIMEOUT}
fi


jobid=$(basename ${INPUT_FILES_DIR})
export jobdir=${CHROOT}/tmp/${jobid}
mkdir -p ${jobdir}
cp ${INPUT_FILES_DIR}/main.cpp ${jobdir}/main.cpp


#
# Enrich the user command with security settings.
#
cmdfile=${jobid}/cmd.sh
chmod -R a+w ${jobdir}

CMD="set -e
ulimit -u 16
ulimit -f 4000
export LD_LIBRARY_PATH=/usr/local/lib
cd /tmp/${jobid}
set +e
$(cat ${INPUT_FILES_DIR}/cmd.sh)"
setsid sudo -u sandbox chroot ${CHROOT} bash -c "${CMD}"
