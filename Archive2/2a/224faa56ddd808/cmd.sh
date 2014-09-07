set -x
clang++ -std=c++1y -O2 -stdlib=libc++ main.cpp -Wall -Wextra -pedantic && ./a.out
g++ -std=c++1y -O2 main.cpp -Wall -Wextra -pedantic && ./a.out