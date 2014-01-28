##set -x ; clang++ -std=c++11 -O3 -W -Wall -Wconversion  -pedantic -pthread main.cpp  && ./a.out
set -x ; g++ -std=c++11 -O0 -W -Wall  -Wconversion -pedantic -pthread main.cpp  && ./a.out