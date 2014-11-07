echo llvm && clang++ -std=c++14 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out 
echo gnu && g++ -std=c++14 -O2 -Wall -Wextra -pedantic-errors main.cpp && ./a.out