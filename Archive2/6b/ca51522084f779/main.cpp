#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> x(11);
std::atomic<int> y;

void foo()
{
    int expected = 11;
    while(!x.compare_exchange_strong(expected, 42, std::memory_order_seq_cst))
    {
        expected = 11;
    }
    
    std::cout << y.load(std::memory_order_relaxed) << " ";
    y.store(21, std::memory_order_relaxed);
    
    std::atomic<int> z;
    z.store(0, std::memory_order_seq_cst);
    
    x.store(11, std::memory_order_relaxed); // can this be moved above z.store?
}

int main()
{
    auto x = std::thread(foo);
    auto y = std::thread(foo);
    
    x.join();
    y.join();
}