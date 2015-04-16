set -x;
g++-4.9 -std=c++14 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -Wconversion -pthread main.cpp && ./a.out
clang++ -std=c++14 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread -stdlib=libc++ main.cpp -lsupc++ && ./a.out
# clang++ -std=c++11 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -Wconversion -pthread main.cpp && ./a.out