#include "tbb/concurrent_queue.h"
#include <iostream>
#include <thread>


// lock-free queue used as a pool of int*
tbb::concurrent_bounded_queue<int*> queue;


// this thread pre-allocates int* and puts them in the queue
std::thread allocator_thread([]{
    static unsigned n = 0; // use counter for testing purposes
    for(;;) queue.push(new int(n++)); // push(...) blocks once queue is full
});


// grabs an int* from the queue (caller gets ownership)
int* alloc_int()
{
    int* n;
    queue.pop(n);
    return n;
}


int main()
{
    std::cout << *alloc_int() << std::endl;
    std::cout << *alloc_int() << std::endl;
    std::cout << *alloc_int() << std::endl;
    std::cout << *alloc_int() << std::endl;
    
    // todo: join allocator_thread (std::terminate is called)
}