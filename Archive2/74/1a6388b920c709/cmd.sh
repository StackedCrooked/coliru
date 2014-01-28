clang++ -std=c++11 -O3 -Wall -Wextra -Wno-uninitialized -pedantic-errors main.cpp && ./a.out
echo ---------------------------------------------------------------------------------------
clang++ -std=c++11 -O3 -Wall -Wextra -Wno-uninitialized -pedantic-errors -DNDEBUG main.cpp && ./a.out