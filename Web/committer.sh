#!/bin/bash
set -e
source coliru_env.source
[ -z ${COLIRU_ARCHIVE} ] && { echo "COLIRU_ARCHIVE variable must be set." && exit 1; }
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }

while true ; do
  # Add new files to subversion.
  (cd ${COLIRU_ARCHIVE} && svn st --no-ignore | grep -e ^[I?] | sed 's_^[?I][ ]*__' | xargs -I {} svn add -q ${COLIRU_ARCHIVE}/{} >committer.log 2>&1)

  # And commit them.
  svn ci ${COLIRU_ARCHIVE} -m "Update archive" >committer.log 2>&1

  # Also commit the feedback."
  svn ci feedback.txt -m "Update feedback." >committer.log 2>&1

  # Repeat later. 
  sleep 1200
done
