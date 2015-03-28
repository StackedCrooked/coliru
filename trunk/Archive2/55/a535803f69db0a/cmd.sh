g++ -std=c++14 -O0 -Wall -pedantic -DCLANG_FIX=0 main.cpp && ./a.out
g++ -std=c++14 -O0 -Wall -pedantic -DCLANG_FIX=1 main.cpp && ./a.out
clang++ -std=c++14 -O0 -Wall -pedantic -DCLANG_FIX=0 main.cpp && ./a.out
clang++ -std=c++14 -O0 -Wall -pedantic -DCLANG_FIX=1 main.cpp && ./a.out