set -x;
g++ -O3 -std=c++1y -Wall -Wextra -pedantic -pthread main.cpp && ./a.out
clang++ -O3 -std=c++1y -Wall -Wextra -pedantic -pthread main.cpp && ./a.out
clang++ -O3 -stdlib=libc++ -std=c++1y -Wall -Wextra -pedantic -pthread main.cpp && ./a.out