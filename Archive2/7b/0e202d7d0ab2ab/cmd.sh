printf 'sed|wc:  line count excluding comments and empty lines: ' 
sed -e 's/[ \t]*\/\/.*$//' -e '/^$/d; /^\s*$/d' main.cpp | wc -l

clang++ -std=c++11 -Wall -Wextra -pedantic-errors -O3 main.cpp 
./a.out main.cpp