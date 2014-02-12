g++-4.8 -std=c++11 -Wall -Wextra -pedantic-errors -O3 main.cpp&& ./a.out
echo -e '\n--------------------------------------------------------\n'
clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 main.cpp -lsupc++ && ./a.out