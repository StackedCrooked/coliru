#!/bin/bash
set -x
exec 1> >(logger -t $0)
exec 2> >(logger -t $0)
source coliru_env.source
[ -z ${COLIRU_ARCHIVE} ] && { echo "COLIRU_ARCHIVE variable must be set." && exit 1; }
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }

SLEEP_DURATION=3600

while true ; do
  # Add new files to subversion.
  (cd ${COLIRU_ARCHIVE} && svn st --no-ignore | grep -e ^[I?] | sed 's_^[?I][ ]*__' && xargs svn add && svn ci -m "Update Archive.")

  # Also commit the feedback."
  echo "Committing any new feedback..."
  svn ci feedback.txt -m "Update feedback." || echo "...but there is no new feedback."

  # Repeat later. 
  echo "Sleeping for ${SLEEP_DURATION} seconds until retry."
  sleep ${SLEEP_DURATION}
done
