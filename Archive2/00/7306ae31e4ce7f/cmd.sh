g++ -std=c++11 -Wall -pedantic -pthread main.cpp && ./a.out
echo -----
clang++ -std=c++11 -Wall -pedantic -pthread main.cpp && ./a.out
echo -----
g++-4.9 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out