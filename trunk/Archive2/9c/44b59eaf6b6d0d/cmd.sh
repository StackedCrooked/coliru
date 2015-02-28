run() { export n=$1 ; cmd="g++ -c -DA=$n -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -S -o - | wc -c" ; echo "$cmd => code size is $(eval "$cmd")" ; }
run 1 ;  run 2 ; run 3