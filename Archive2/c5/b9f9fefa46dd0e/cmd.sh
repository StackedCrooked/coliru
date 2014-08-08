ln -s /Archive2/52/78a7e25631946e/main.cpp source.cpp
g++ -c -std=c++11 -O3 -Wall -pedantic main.cpp
g++ -c -std=c++11 -O3 -Wall -pedantic source.cpp
g++ main.o source.o
./a.out