set -x
clang++ -std=c++1y -stdlib=libc++ main.cpp -Wall -Wextra -pedantic && ./a.out
g++ -std=c++1y main.cpp -Wall -Wextra -pedantic && ./a.out