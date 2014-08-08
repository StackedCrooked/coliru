ln -s /Archive2/bf/62399c690ea7c4/main.cpp source.cpp
g++ -c -std=c++11 -O2 -Wall -pedantic main.cpp
g++ -c -std=c++11 -O2 -Wall -pedantic source.cpp
g++ main.o source.o
./a.out
echo done