#include <future>
#include <iostream>
#include <thread>


template<typename T>
class ready_future : private std::promise<T>, public std::future<T>
{
public:    
    ready_future(T&& t) : std::future<T>(this->get_future())
    {
        this->set_value(t);
    }
};

template<>
class ready_future<void> : private std::promise<void>, public std::future<void>
{
public:    
    ready_future() : std::future<void>(this->get_future())
    {
        this->set_value();
    }
};


using namespace std::chrono;
using Clock = high_resolution_clock;


std::future<void> wait_until_time(Clock::time_point time)
{
    if (time <= Clock::now())
    {
        return ready_future<void>(); // *** SLICING! ***
                                     // Safe?
    }
    
    return std::async(std::launch::async, [=]{ std::this_thread::sleep_until(time); });
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