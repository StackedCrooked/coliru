ln -s /Archive2/c0/64cb2b335eb708/main.cpp source.cpp
g++ -c -std=c++11 -O3 -Wall -pedantic main.cpp
g++ -c -std=c++11 -O3 -Wall -pedantic source.cpp
g++ main.o source.o
./a.out