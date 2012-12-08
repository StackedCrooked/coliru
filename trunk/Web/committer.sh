while true ; do svn add * 2>/dev/null ; svn ci -m "Update Archive. ${RANDOM}" ; sleep 60 ; done
