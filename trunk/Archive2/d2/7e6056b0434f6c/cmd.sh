set -x ;
g++ -std=c++1y -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion main.cpp && ./a.out
clang++ -std=c++1y -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion -stdlib=libc++ main.cpp -lsupc++ && ./a.out