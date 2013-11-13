#!/bin/bash

# Prepare the job directory
jobid=$(basename ${INPUT_FILES_DIR})
export jobdir=${CHROOT}/tmp/${jobid}
mkdir -p ${jobdir}
cp ${INPUT_FILES_DIR}/main.cpp ${jobdir}/main.cpp
chmod -R a+w ${jobdir}

# Prepare the command.
CMD="set -e
ulimit -u 16
ulimit -f 4000
ulimit -t 10
export LD_LIBRARY_PATH=/usr/local/lib
cd /tmp/${jobid}
set +e
$(cat ${INPUT_FILES_DIR}/cmd.sh)"

# Run the command in the chroot and create a new pgid.
setsid sudo -u sandbox chroot ${CHROOT} bash -c "${CMD}"
