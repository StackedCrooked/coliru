ln -s /Archive2/aa/7953dc42bc50f4/main.cpp count_bits.cpp
g++-4.8 -std=c++11 -O3 -Wall -Wextra -pedantic-errors -c count_bits.cpp
ln -s /Archive2/f5/f3309f6603e569/main.cpp count_bits2.cpp
g++-4.8 -std=c++11 -O3 -Wall -Wextra -pedantic-errors -c count_bits2.cpp
g++-4.8 -std=c++11 -O3 -Wall -Wextra -pedantic-errors -O3 main.cpp *.o && ./a.out