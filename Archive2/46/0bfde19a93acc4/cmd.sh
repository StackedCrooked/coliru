echo 'llvm libc++'
clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -pedantic -pthread main.cpp -lsupc++ && ./a.out
echo 'gnu libstdc++'
g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out