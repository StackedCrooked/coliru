#!/bin/bash
set -x
exec 1> >(logger -t "$0 stdout")
exec 2> >(logger -t "$0 stderr")
echo "Starting the committer."
echo "Loading the environment variables."
source coliru_env.source
[ -z ${COLIRU_ARCHIVE} ] && { echo "COLIRU_ARCHIVE variable must be set." && exit 1; }
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }

SLEEP_DURATION=3600

while true ; do
    # Update archive 
    echo "Update the archive"
    (cd ${COLIRU_ARCHIVE} && svn up)

    # Commit archive changes
    echo "Commit the archive"
    (cd ${COLIRU_ARCHIVE} && svn ci -m "Archive changes.")

    # Add new files to subversion.
    echo "Commit any new archives."
    (
        cd ${COLIRU_ARCHIVE}
        { svn st --no-ignore | grep -e ^[I?] | sed 's_^[?I][ ]*__' | xargs svn add && svn ci -m "Update Archive." ; } || svn cleanup
    )

    # Also commit the feedback."
    echo "Committing any new feedback..."
    svn ci feedback.txt -m "Update feedback." || echo "...but there is no new feedback."

    # Repeat later. 
    echo "Sleeping for ${SLEEP_DURATION} seconds until retry."
    sleep ${SLEEP_DURATION}
done
