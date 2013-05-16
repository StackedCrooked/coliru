#!/bin/bash
[ "$INPUT_FILES_DIR" == "" ] && { echo "INPUT_FILES_DIR is not set." 1>&2 ; exit 1 ; }
[ "$INPUT_FILES_DIR" == "." ] && { echo "INPUT_FILES_DIR is jsut a dot." 1>&2 ; exit 1 ; }
export INPUT_FILES_DIR
echo "INPUT_FILES_DIR is ${INPUT_FILES_DIR} " >> webserver.log
echo "INPUT_FILES_DIR constains $(ls ${INPUT_FILES_DIR}) " >> webserver.log

# Make the archive id
ID="$(md5sum ${INPUT_FILES_DIR}/main.cpp | cut -d ' ' -f 1)-$(md5sum ${INPUT_FILES_DIR}/cmd.sh | cut -d ' ' -f 1)"

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

chmod 755 ${INPUT_FILES_DIR}/cmd.sh
cat ${INPUT_FILES_DIR}/main.cpp > ${DIR}/main.cpp
cat ${INPUT_FILES_DIR}/cmd.sh > ${DIR}/cmd.sh
date '+%s' > ${DIR}/timestamp


{ ./build_and_run.sh >"${DIR}/output" 2>&1 ; } || true
{ rsync -a --exclude=.svn ${DIR} /var/chroot/Archive/ ; } || true
