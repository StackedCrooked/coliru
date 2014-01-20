echo "with -Wno-unused-variable"
g++-4.8 -std=c++11 -O2 -Wall -Wextra -pedantic-errors -Wno-unused-variable main.cpp && ./a.out