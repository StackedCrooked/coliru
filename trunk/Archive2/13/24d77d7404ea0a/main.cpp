#include <chrono>
#include <future>
#include <iostream>


int main()
{
    std::cout << "Using GCC " << __VERSION__ << ": ";
    
    auto f = std::async(std::launch::deferred, []{});
    switch (f.wait_for(std::chrono::seconds(0)))
    {
        case std::future_status::deferred: std::cout << "deferred" << std::endl; break;
        case std::future_status::timeout: std::cout << "timeout" << std::endl; break;
        case std::future_status::ready: std::cout << "ready" << std::endl; break;
    }
}
