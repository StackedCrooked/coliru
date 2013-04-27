#!/bin/bash
[ -z ${COLIRU_ARCHIVE} ] && { echo "COLIRU_ARCHIVE variable must be set." && exit 1; }
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }

while true ; do
  # Add new files to subversion.
  (cd ${COLIRU_ARCHIVE} && svn st --no-ignore | grep -e ^[I?] | sed 's_^[?I][ ]*__' | xargs -I {} svn add -q ${COLIRU_ARCHIVE}/{})

  # And commit them.
  svn ci ${COLIRU_ARCHIVE} -m "Update archive"

  # Also commit the feedback."
  svn ci feedback.txt -m "Update feedback."

  # Copy the archive to the chroot
  { rsync -az --exclude=.svn ${COLIRU_ARCHIVE} /var/chroot/ && chmod -R a+rx /var/chroot/Archive ; } & disown

  # Repeat later. 
  sleep 1200
done
