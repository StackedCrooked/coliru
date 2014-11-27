set -x; g++ -std=c++14 -O2 -Wall -Wextra -pedantic -pthread main.cpp -lm  && ./a.out
clang++ -std=c++14 -O2 -Wall -Wextra -pedantic -pthread main.cpp -lm  && ./a.out