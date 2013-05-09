#!/bin/bash
source coliru_env.source
[ -z ${COLIRU_ARCHIVE} ] && { echo "COLIRU_ARCHIVE variable must be set." && exit 1; }
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }

# sleep duration is 20 seconds
SLEEP_DURATION=20

while true ; do
  # Add new files to subversion.
  for i in $(ls -tc1 ${COLIRU_ARCHIVE}) ; do
    DIR="${COLIRU_ARCHIVE}/${i}"
    [ -d ${DIR} ] && [ ! -d "${DIR}/.svn" ] && { echo "Adding ${DIR} to svn." ; svn add ${DIR} ; svn ci ${DIR} -m "Add to archive." ; sleep 1 ; }
  done
  echo "Finished checking for new posts."

  # Also commit the feedback."
  echo "Committing any new feedback..."
  svn ci feedback.txt -m "Update feedback." || echo "...but there is no new feedback."

  # Repeat later. 
  echo "Sleeping for ${SLEEP_DURATION} seconds until retry."
  sleep ${SLEEP_DURATION}
done
