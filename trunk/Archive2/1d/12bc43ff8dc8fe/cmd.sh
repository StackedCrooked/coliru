#title Thread-safe (?) refcounted object
touch PacketGroup.h
clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out