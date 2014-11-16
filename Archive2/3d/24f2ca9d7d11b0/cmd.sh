set -x;
g++ -std=c++11 -fno-elide-constructors  -O2 -pedantic  main.cpp && ./a.out
clang++ -std=c++11 -fno-elide-constructors  -O2  -pedantic  main.cpp && ./a.out