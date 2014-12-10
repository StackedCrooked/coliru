clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && echo clang++ says OK || echo clang nok
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && echo g++ ok || echo g++ says NOT OK