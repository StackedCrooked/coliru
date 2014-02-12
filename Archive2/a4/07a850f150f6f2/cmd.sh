ln -s /Archive2/f4/b250832bdf4335/main.cpp foo.cpp
clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 -c -march=native foo.cpp
clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 -march=native main.cpp foo.o -lsupc++ && time ./a.out