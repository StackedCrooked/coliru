g++ -std=c++11 -O2 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out