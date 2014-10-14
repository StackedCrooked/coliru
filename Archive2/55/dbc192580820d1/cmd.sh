echo '10' > input.txt
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out < input.txt