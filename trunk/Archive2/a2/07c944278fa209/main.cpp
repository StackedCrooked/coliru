#include <future>
#include <iostream>

int main()
{
    switch (std::async([]{}).wait_for(std::chrono::seconds(100)))
    {
        case std::future_status::ready: std::cout << "ready"; break;
        case std::future_status::deferred: std::cout << "deferred"; break;
        case std::future_status::timeout: std::cout << "timeout"; break;
    };
}