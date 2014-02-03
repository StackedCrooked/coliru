clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out
clang++ -std=c++11 -DUSE_D -stdlib=libc++ -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out