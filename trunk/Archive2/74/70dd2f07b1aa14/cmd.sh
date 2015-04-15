echo -e "g++:\n"; g++ -std=c++14 -O2 -Wall -Wno-unused -pedantic -pthread main.cpp
echo -e "clang++:\n"; clang++ -std=c++14 -O2 -Wall -Wno-unused -pedantic -pthread main.cpp