echo "ls
pwd
date" >commands
while read line ; do printf "comand=$line\noutput=$(eval $line | perl -pe 's,\n,\\\\n,g')\n" ; done <commands