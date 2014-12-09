clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -stdlib=libc++ && ./a.out
clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -stdlib=libstdc++ && ./a.out
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp  && ./a.out