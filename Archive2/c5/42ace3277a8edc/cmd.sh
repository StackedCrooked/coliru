ln -s /Archive2/b3/8e8cfad11cfdea/main.cpp foo.cpp
g++-4.8 -std=c++11 -Wall -Wextra -pedantic-errors -O3 -c -fomit-frame-pointer -march=native foo.cpp
g++-4.8 -std=c++11 -Wall -Wextra -pedantic-errors -O3 -fomit-frame-pointer -march=native main.cpp foo.o && time ./a.out