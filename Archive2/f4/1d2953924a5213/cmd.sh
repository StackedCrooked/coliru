ln -s /Archive2/0d/759b1f550f70f0/main.cpp Bitmask.h 
ln -s /Archive2/c7/823a828288e5e3/main.cpp Bitmask.cpp
g++ -std=c++11 -O2 -Wall -Wextra -pedantic-errors main.cpp Bitmask.cpp && ./a.out