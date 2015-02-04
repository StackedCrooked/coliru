#title TBB fibonacci wrapped inside function
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -ltbb && timeout 5 ./a.out