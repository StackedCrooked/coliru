ln -s /Archive2/bb/27088855a3d8a4/main.cpp foo.cpp
clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 -c foo.cpp
clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 main.cpp foo.o -lsupc++ && time ./a.out