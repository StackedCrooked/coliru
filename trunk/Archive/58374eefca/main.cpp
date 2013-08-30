echo "ls
pwd
date" >commands
while read line ; do printf "\"$line\" : \"$(eval $line | perl -pe 's,\n,\\\\n,g')\"\n" ; done <commands
