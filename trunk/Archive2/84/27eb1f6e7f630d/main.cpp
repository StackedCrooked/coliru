#include <thread>
#include <mutex>
#include <iostream>

int main()
{
    std::mutex x;
    std::unique_lock<std::mutex> lock(x);

    auto f = [](std::unique_lock<std::mutex> lock)
    {
        std::cout << "thread";
    };

    std::thread t(f, std::move(lock));
    
    t.join();
}
