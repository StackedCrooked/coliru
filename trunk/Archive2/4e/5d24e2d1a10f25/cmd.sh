set -x; clang++ -std=c++11 -O -Wall -Wextra -pedantic -Wno-unused -pthread main.cpp && ./a.out
clang++ -std=c++11 -DBAD_CASE -O -Wall -Wextra -pedantic -Wno-unused -pthread main.cpp && ./a.out