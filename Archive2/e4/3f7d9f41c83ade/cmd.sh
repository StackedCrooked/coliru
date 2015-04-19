set -x; clang++ -std=c++1y -stdlib=libc++ -Wall -pedantic main.cpp -pthread -lcxxrt -ldl && ./a.out
clang++ -std=c++1y -Wall -pedantic main.cpp -pthread -lcxxrt -ldl && ./a.out
g++ -std=c++1y -Wall -pedantic main.cpp -pthread && ./a.out