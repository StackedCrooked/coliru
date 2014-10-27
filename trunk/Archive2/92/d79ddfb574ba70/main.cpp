#include <iostream>
#include <memory>
#include <vector>
#include <atomic>
#include <thread>

struct Node {
    int number;
    std::atomic_bool latch;
    
    Node() : number() {}
    void add()
    {
        lock();
        ++number;
        unlock();
    }
    
    void lock()
    {
        bool unlatched;
        while(!latch.compare_exchange_weak(unlatched, true, std::memory_order_acquire))
            unlatched = false;
    }
    
    void unlock()
    {
        latch.store(false, std::memory_order_release);
    }
};

void thread_proc(Node& node)
{
    for (int i=0; i<1000000; ++i)
        node.add();
}

int main()
{
    Node node;
    std::thread t1(thread_proc, std::ref(node));
    std::thread t2(thread_proc, std::ref(node));
    t1.join();
    t2.join();
    std::cout << node.number << '\n';
}