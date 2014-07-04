g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && time ./a.out &&
g++ -std=c++11 -O2 -Wall -pedantic -pthread -DCSTYLE main.cpp && time ./a.out