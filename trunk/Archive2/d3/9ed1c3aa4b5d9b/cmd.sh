echo === g++ ===
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
echo
echo === clang ===
clang -std=c++14 -O2 -pedantic main.cpp && ./a.out