set +x
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp
for i in $(seq 12) ; do ./a.out $((2 ** $i))  ; done | column -t