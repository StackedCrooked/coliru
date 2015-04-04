#title Function wrapper using function pointer and optional small storage and/or custom allocator.
echo "GCC: " ; g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
echo "CLANG: "; clang++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out