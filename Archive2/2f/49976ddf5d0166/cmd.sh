#title scoped_allocator_adaptor nesting example (NOTE: only works for clang)
clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -pedantic -pthread main.cpp && ./a.out
#g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out