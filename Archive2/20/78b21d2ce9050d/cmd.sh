set -x;
clang++ -O0 -Wall -pedantic -Wextra -pthread -std=c++1y main.cpp && ./a.out
clang++ -O0 -Wall -pedantic -Wextra -pthread -std=c++1y -stdlib=libc++ main.cpp -lsupc++ && ./a.out