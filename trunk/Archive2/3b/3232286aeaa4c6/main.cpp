#include <future>
#include <iostream>
#include <thread>


using namespace std::chrono;
using Clock = high_resolution_clock;


void print(std::future<void> fut)
{    
    switch (fut.wait_for(std::chrono::seconds(0)))
    {
        case std::future_status::ready: std::cout << "ready\n"; break;
        case std::future_status::deferred: std::cout << "deferred\n"; break;
        case std::future_status::timeout: std::cout << "timeout\n"; break;
    };
}


int main()
{    
    print(std::async(std::launch::deferred, []{}));
    
    auto fut = std::async(std::launch::deferred, []{});
    fut.wait();
    print(std::move(fut));
}