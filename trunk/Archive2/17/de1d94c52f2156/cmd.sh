set -x; clang++ -stdlib=libc++ -std=c++14 -O2 -Wextra -Wall -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out
g++ -std=c++14 -O2 -W -Wall -pedantic -pthread main.cpp && ./a.out