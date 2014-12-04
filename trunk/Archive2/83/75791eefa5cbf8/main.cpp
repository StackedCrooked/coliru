#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <chrono>

int main()
{
    std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;
    std::cout << "Hardware concurrency: " << std::thread::hardware_concurrency() << std::endl;
    
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 10; ++i)
    {
        auto fut = std::async([i]
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << std::this_thread::get_id() << " ";
        });
        futures.push_back(std::move(fut));
    }
} 