ln -s /Archive2/52/78a7e25631946e/main.cpp source.cpp
clang++ -c -std=c++11 -O3 -Wall -pedantic main.cpp
clang++ -c -std=c++11 -O3 -Wall -pedantic source.cpp
clang++ main.o source.o
./a.out