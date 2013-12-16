#include <future>
#include <iostream>
#include <thread>


using namespace std::chrono;
using Clock = high_resolution_clock;


std::future<void> wait_until_time(Clock::time_point time)
{    
    return std::async([=]{ std::this_thread::sleep_until(time); });
}


void test(std::future<void> fut)
{    
    switch (fut.wait_for(std::chrono::milliseconds(500)))
    {
        case std::future_status::ready: std::cout << "ready\n"; break;
        case std::future_status::deferred: std::cout << "deferred\n"; break;
        case std::future_status::timeout: std::cout << "timeout\n"; break;
    };
}


int main()
{    
    test(wait_until_time(Clock::now() - seconds(1)));
    test(wait_until_time(Clock::now() + seconds(1)));
}