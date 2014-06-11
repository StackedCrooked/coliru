#include <iostream>
#include <thread>
#include <array>
#include <functional>

using thread_container = std::array<std::thread, 10>;

void foo() { std::cout << "foo()\n"; }

void thread_joiner(thread_container&) { }

int main()
{
    thread_container threads;
    for (auto& t : threads)
        t = std::thread(foo);
        
    std::thread ct1(thread_joiner, std::ref(threads)), ct2(thread_joiner, std::ref(threads));
    ct1.join();
    ct2.join();
    
    for (auto& t : threads)
        t.join();
}
