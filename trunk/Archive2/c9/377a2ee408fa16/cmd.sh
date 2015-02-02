echo "clang" && clang++ -std=c++11 -O2 -g -Wall -Wextra -pedantic --stdlib=libc++ main.cpp && ./a.out
echo
echo "gcc" && g++ -std=c++11 -O2 -g -Wall -Wextra -pedantic main.cpp && ./a.out