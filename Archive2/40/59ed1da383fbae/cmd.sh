g++ -std=c++11 main.cpp && ./a.out >gcc
clang++ -std=c++11 main.cpp && ./a.out >clang
diff -y gcc clang