ln -s /Archive2/fd/2449d5921648c7/main.cpp foo.cpp 
clang++ -std=c++11 -stdlib=libc++ -O3 -Wall -pedantic-errors -c foo.cpp
clang++ -std=c++11 -stdlib=libc++ -O3 -Wall -pedantic-errors main.cpp foo.o -lsupc++
./a.out
g++-4.8 -std=c++11 -O3 -Wall -pedantic-errors -c foo.cpp
g++-4.8 -std=c++11 -O3 -Wall -pedantic-errors main.cpp foo.o
./a.out