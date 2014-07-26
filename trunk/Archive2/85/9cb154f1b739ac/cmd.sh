g++ -std=c++11 -O1 -S main.cpp
grep -o '_Z[A-Z0-9a-z_]*' main.s >result.txt
count=0
while read p; do
  let count++
  echo $count "Demangling :" $p "--->"
  c++filt -n -t -i $p
  echo 
done <result.txt