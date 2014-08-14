set -x
#g++ -O2 -std=c++11 -pedantic -Wall -pthread main.cpp && ./a.out
clang++ -O2 -std=c++11 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ -O2 -std=c++98 -Wall -pedantic -pthread main.cpp && ./a.out