set -x; g++ -v -std=c++1y -O2 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out
clang++ -stdlib=libc++ -std=c++1y -O2 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out