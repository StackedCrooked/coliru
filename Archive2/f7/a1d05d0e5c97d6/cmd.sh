set -x; clang++ -std=c++11 -stdlib=libc++ -O3 -Wall -Wextra -Wno-missing-braces -pedantic -pthread main.cpp && ./a.out
g++ -std=c++11 -O3 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out