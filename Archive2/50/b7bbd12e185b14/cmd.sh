#title Stack (member) allocator with std::packaged_task
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out | c++filt