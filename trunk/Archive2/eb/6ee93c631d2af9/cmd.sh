ln -s /Archive2/bb/27088855a3d8a4/main.cpp foo.cpp
clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 main.cpp foo.cpp -lsupc++ && time ./a.out