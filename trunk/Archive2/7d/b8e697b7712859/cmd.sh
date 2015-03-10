set -x; g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
#clang++ -std=c++11 -O2 -Wall -pedantic -stdlib=libc++ -pthread main.cpp -lcxxrt -ldl && ./a.out