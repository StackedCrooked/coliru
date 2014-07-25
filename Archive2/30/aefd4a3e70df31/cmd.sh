set -x; g++ -std=c++1y -Wall -O3 -pthread -pedantic main.cpp && ./a.out
clang++ -stdlib=libc++ -std=c++1y -O3 -Wall -pthread -pedantic main.cpp -lcxxrt -ldl  && ./a.out