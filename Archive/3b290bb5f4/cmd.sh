echo "g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp
echo a && b
./a.out" >commands

while read line ; do printf "<line>\n  <command>${line}</command>\n  <output>$(eval "$line 2>&1")</output>\n</line>\n" ; done <commands
printf "\nOr:\n"
while read line ; do printf "cmd=${line}\nout=$(echo "$(eval "$line" 2>/dev/null)")\nerr=$(echo "$(eval "$line" 2>&1 1>/dev/null)")\n" ; done <commands