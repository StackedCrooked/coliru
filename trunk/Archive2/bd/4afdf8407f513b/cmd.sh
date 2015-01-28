# clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out <<< nnnyynnnnn
# g++ -std=c++14 -O3 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
clang -std=c99 -O3 -Wall -Wextra -pedantic-errors -x c main.cpp && ./a.out