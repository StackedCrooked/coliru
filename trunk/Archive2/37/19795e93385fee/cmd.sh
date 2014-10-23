ln -s main.cpp main.c && clang -std=c11 -Wall -Wextra -pedantic-errors -S -c main.c && echo 'c ok'
clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors -S -c main.cpp || echo 'c++ not ok'