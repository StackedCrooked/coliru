set -x;
clang++ -O0 -Wall -Wextra -Wconversion -pedantic -std=c++03 main.cpp && ./a.out
clang++ -O0 -Wall -Wextra -Wconversion -pedantic -std=c++11 main.cpp && ./a.out
g++-4.8 -O0 -Wall -Wextra -Wconversion -pedantic -std=c++11 main.cpp && ./a.out