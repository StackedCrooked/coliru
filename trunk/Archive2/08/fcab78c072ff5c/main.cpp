#include <thread>
#include <atomic>
#include <cassert>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

std::atomic<std::string*> ptr;
int data;
 
void producer()
{
    std::string* p  = new std::string("Hello");
    data = 42;
    std::chrono::milliseconds dura( 2000 );
    std::this_thread::sleep_for( dura );
    ptr.store(p, std::memory_order_release);
}
 
void consumer()
{
    std::string* p2;
    (p2 = ptr.load(std::memory_order_acquire))
        ;
    cout << p2 << endl;
    assert(*p2 == "Hello"); // never fires
    assert(data == 42); // never fires
}
 
int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join(); t2.join();
    cout << "gogo" << endl;
}