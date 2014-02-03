#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <chrono>

int main()
{
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::time_point<Clock> Timestamp;
    typedef std::chrono::nanoseconds Duration;

    Timestamp st, en;
    
    st = Clock::now();
    std::array<std::mutex, 10000> locks;
    en = Clock::now();
    std::cout << "Construct mutex elapsed: " << std::chrono::duration_cast<Duration>(en - st).count() / 10000 << "ns each" << std::endl;

    st = Clock::now();
    std::array<std::unique_lock<std::mutex>, 10000> holders;
    en = Clock::now();
    std::cout << "Construct unique_lock elapsed: " << std::chrono::duration_cast<Duration>(en - st).count() / 10000 << "ns each" << std::endl;

    st = Clock::now();
    for (auto i = 0; i < 10000; ++i)
        holders[i] = std::unique_lock<std::mutex>(locks[i]);
    en = Clock::now();
    std::cout << "Acquire unique_lock elapsed: " << std::chrono::duration_cast<Duration>(en - st).count() / 10000 << "ns each" << std::endl;

    st = Clock::now();
    for (auto i = 0; i < 10000; ++i)
        holders[i].unlock();
    en = Clock::now();
    std::cout << "Release unique_lock elapsed: " << std::chrono::duration_cast<Duration>(en - st).count() / 10000 << "ns each" << std::endl;

    std::cout << "Size: " << sizeof(std::mutex) << std::endl;
}
