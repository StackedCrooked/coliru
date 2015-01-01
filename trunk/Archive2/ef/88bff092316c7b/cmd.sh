#title scoped_allocator_adaptor test
clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -pedantic -pthread main.cpp && ./a.out ; printf "\nExited with code $?.\n"