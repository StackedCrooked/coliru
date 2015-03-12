set -x;
clang++ -std=c++14 -O0 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -stdlib=libc++ -pthread main.cpp -lsupc++ && ./a.out
g++-4.9 -std=c++14 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread -Wconversion main.cpp -lboost_system && ./a.out
# clang++ -std=c++11 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread -Wconversion main.cpp && ./a.out