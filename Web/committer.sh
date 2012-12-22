while true ; do ls -tc1 Archive | xargs -I {} svn add Archive/{} ; svn ci Archive -m "Update archive" ; sleep 3600 ; done
