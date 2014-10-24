#include <thread>
#include <atomic>
#include <cassert>
#include <string>
 
std::atomic<std::string*> ptr;
int data;
 
void producer1()
{
    std::string* p  = new std::string("Hello producer 1");
    data = 41;
    ptr.store(p, std::memory_order_release);
    printf("producer1\n");
}
 
void producer2()
{
    std::string* p  = new std::string("Hello producer 2");
    data = 42;
    ptr.store(p, std::memory_order_release);
    printf("producer2\n");
} 
 
void consumer()
{
    std::string* p2;
    while (!(p2 = ptr.load(std::memory_order_acquire)))
        ;
    //assert(*p2 == "Hello producer 1"); // never fires
    if (*p2 == "Hello producer 1")
    {printf("consumer & Hello producer 1\n");}
    else if (*p2 == "Hello producer 2")
    {printf("consumer & Hello producer 2\n");}
    
    //assert(data == 42); // never fires
    if (data == 42)
    {printf("data 42\n");}
    else
    {printf("data 41\n");}
    
    
}
 
int main()
{
    std::thread t1(producer1);
    std::thread t2(producer2);
    std::thread t3(consumer);
    t1.join(); 
    t2.join();
    t3.join();
    
    printf("finished");
}