#include <future>
#include <iostream>


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

int main()
{
    //switch (std::async([]{}).wait_for(std::chrono::milliseconds(1)))
    ready_future<void> ready;
    switch (ready.wait_for(std::chrono::milliseconds(1)))
    {
        case std::future_status::ready: std::cout << "ready"; break;
        case std::future_status::deferred: std::cout << "deferred"; break;
        case std::future_status::timeout: std::cout << "timeout"; break;
    };
}