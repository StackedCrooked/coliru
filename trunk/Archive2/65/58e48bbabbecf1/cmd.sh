echo -e '--------------------------  WITH_RVALUE_OVERLOAD -------------------------------------\n'
clang++ -DWITH_RVALUE_OVERLOAD -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out
echo -e '--------------------- DISABLE_ON_RVALUES (compile-time error) ------------------------\n'
clang++ -DDISABLE_ON_RVALUES -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out