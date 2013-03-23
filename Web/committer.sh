#!/bin/sh
[ -z ${COLIRU_ARCHIVE} ] && { echo "COLIRU_ARCHIVE variable must be set." && exit 1; }
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }

while true ; do
  # Copy the archive to the chroot
  rsync -az --exclude=.svn ${COLIRU_ARCHIVE} /var/chroot/ && chmod -R a+rx /var/chroot/Archive

  # Add new files to subversion.
  ls -tc1 ${COLIRU_ARCHIVE} | xargs -I {} svn add -q ${COLIRU_ARCHIVE}/{}

  # And commit them.
  svn ci ${COLIRU_ARCHIVE} -m "Update archive"

  # Repeat later. 
  sleep 1200
done
