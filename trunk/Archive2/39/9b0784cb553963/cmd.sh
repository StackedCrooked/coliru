echo "Compilation with GCC"
echo "********************"
g++-4.8 -std=c++11 -Wall -Wextra -pedantic -O2 main.cpp
./a.out
echo
echo "Compilation with Clang"
echo "**********************"
clang++ -std=c++11 -Wall -Wextra -pedantic -O2 main.cpp
./a.out