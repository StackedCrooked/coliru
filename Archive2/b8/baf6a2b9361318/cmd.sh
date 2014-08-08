ln -s /Archive2/c0/64cb2b335eb708/main.cpp source.cpp
clang++ -c -std=c++11 -O1 -Wall -pedantic main.cpp
clang++ -c -std=c++11 -O1 -Wall -pedantic source.cpp
clang++ main.o source.o
./a.out