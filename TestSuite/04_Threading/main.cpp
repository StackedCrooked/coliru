#include <atomic>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>


std::atomic<bool> stop(false);


int main()
{
    std::mutex mtx;
    uint64_t count = 0;
    std::vector<std::thread> ts;
    for (unsigned i = 0; i != 10; ++i)
    {
        ts.emplace_back([&mtx, &count]{ while (!stop) { std::unique_lock<std::mutex> lock(mtx); count++; } });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    stop = true;

    for (auto & t : ts)
    {
        t.join();
    }

    std::cout << "Counter: " << count << std::endl;
}
