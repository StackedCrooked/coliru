title Simple Worker class
set -e 
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp

start_time="$(date +%s%N)"
export IFS=''
timeout 2 ./a.out | while read -r line ; do
  printf "[$((($(date +%s%N) - $start_time) / 1000000))ms] main.cpp:${line}:\n$(head -n "$(($line + 1))" main.cpp | tail -n3 | while read line; do echo ": $(echo $line)" ; done)\n\n">>out
done
cat out