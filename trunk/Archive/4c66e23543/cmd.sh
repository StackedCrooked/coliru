g++-4.8 -O2 -Wall -Wextra -pedantic -pthread main.cpp 2>&1 | sed "s/^/C:/"; [ -x a.out ] && ./a.out 2>&1 | sed s/^/O:/