#title `std::promise(allocator_arg_t,...)` and `std::allocate_shared`
clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -pedantic -pthread main.cpp -ltbb && ./a.out