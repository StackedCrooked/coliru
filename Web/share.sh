#!/bin/bash
[ "$TMP_DIR" == "" ] && { echo "TMP_DIR is not set." 1>&2 ; exit 1 ; }
[ "$TMP_DIR" == "." ] && { echo "TMP_DIR is jsut a dot." 1>&2 ; exit 1 ; }
export TMP_DIR
echo "TMP_DIR is ${TMP_DIR} " >> webserver.log
echo "TMP_DIR constains $(ls ${TMP_DIR}) " >> webserver.log

# Make the archive id
ID="$(md5sum ${TMP_DIR}/main.cpp | cut -d ' ' -f 1)-$(md5sum ${TMP_DIR}/cmd.sh | cut -d ' ' -f 1)"

# This is the only return 
echo "${ID}"


# If the id already existed then simply return.
# We don't have to compile anymore.
if [ -d "${COLIRU_ARCHIVE}/${ID}" ] ; then
    exit
fi

# The archive directory for the ide.
export DIR=${COLIRU_ARCHIVE}/${ID}
mkdir ${DIR}

chmod 755 ${TMP_DIR}/cmd.sh
cat ${TMP_DIR}/main.cpp > ${DIR}/main.cpp
cat ${TMP_DIR}/cmd.sh > ${DIR}/cmd.sh
date '+%s' > ${DIR}/timestamp


{ ./build_and_run.sh >"${DIR}/output" 2>&1 ; } || true
{ rsync -a --exclude=.svn ${DIR} /var/chroot/Archive/ ; } || true
