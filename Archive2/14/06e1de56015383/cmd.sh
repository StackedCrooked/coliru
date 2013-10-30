g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
./a.out
echo abc | grep b | sed s,b,B,