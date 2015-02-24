g++ -v
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
echo "____________________________"
clang++ -v
clang++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out