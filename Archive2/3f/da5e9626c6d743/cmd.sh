clang++ -std=c++11 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors -c main.cpp && echo 'llvm: ok'
g++-4.9 -std=c++11 -O3 -Wall -Wextra -pedantic-errors -c main.cpp && echo 'gnu: ok'