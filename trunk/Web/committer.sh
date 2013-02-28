#!/bin/sh
[ -z ${COLIRU_ARCHIVE} ] && { echo "COLIRU_ARCHIVE variable must be set." && exit 1; }
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }
while true ; do ls -tc1 ${COLIRU_ARCHIVE} | xargs -I {} svn add -q ${COLIRU_ARCHIVE}/{} ; svn ci ${COLIRU_ARCHIVE} -m "Update archive" ; sleep 3600 ; done
