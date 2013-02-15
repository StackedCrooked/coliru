while true ; do ls -tc1 ${COLIRU_ARCHIVE} | xargs -I {} svn add -q ${COLIRU_ARCHIVE}/{} ; svn ci ${COLIRU_ARCHIVE} -m "Update archive" ; sleep 3600 ; done
