set -x; clang++ -std=c++11 -Wall -Wextra -pedantic -pthread main.cpp -stdlib=libc++ && ./a.out; g++ -std=c++11 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out