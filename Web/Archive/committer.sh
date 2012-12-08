while true ; do svn add * 2>/dev/null ; svn ci -m "Update Archive. ${RANDOM}" ; sleep 10 ; done
