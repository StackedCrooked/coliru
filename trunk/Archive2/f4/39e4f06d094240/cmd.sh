ln -s /Archive2/67/e7b54192f3fdf6/main.cpp globals.h
ln -s /Archive2/40/d1849fd7cbceae/main.cpp globals.cpp
clang++ -std=c++14 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp globals.cpp -lsupc++ && ./a.out