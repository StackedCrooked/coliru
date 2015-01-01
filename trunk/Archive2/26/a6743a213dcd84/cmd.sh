#title std::promise(allocator_arg_t,...) and std::allocate_shared
g++ -std=c++11 -O2 -Wall -pedantic -Wno-enum-compare -pthread main.cpp -ltbb && ./a.out