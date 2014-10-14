set -x
clang++ --version
clang++ -stdlib=libc++ -std=c++1y -Wall -Wextra -pedantic-errors -O3 main.cpp && ./a.out
g++ --version
g++ -std=c++1y -Wall -Wextra -pedantic-errors -O3 main.cpp && ./a.out