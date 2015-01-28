g++ -std=c++11 -O2 -Wall -pedantic -lpthread -c main.cpp -o main.o
g++ -std=c++11 -O2 -Wall -pedantic -lpthread main.o -o main && ./main