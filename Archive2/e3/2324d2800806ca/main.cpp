#include <thread>
#include <atomic>
#include <cassert>
#include <string>
#include <iostream>

std::atomic<std::string*> ptr;
int data;
 
void producer()
{
    std::string* p  = new std::string("Hello");
    data = 42;
    ptr.store(p, std::memory_order_relaxed);
}
 
void consumer()
{
    std::string* p2;
    while (!(p2 = ptr.load(std::memory_order_relaxed)))
        ;
    std::cout<< (*p2 == "Hello") << std::endl;; // never fires
    std::cout << (data == 42) << std::endl; // never fires
}
 
int main()
{
    std::thread t2(consumer);
    std::thread t1(producer);
    
    t1.join(); t2.join();
}