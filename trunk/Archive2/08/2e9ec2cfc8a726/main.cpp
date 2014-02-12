#include <vector>
#include <iostream>
#include <mutex>
#include <chrono>
#include <condition_variable>

int main()
{
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::time_point<Clock> TimePoint;
    
    std::mutex m;
    std::condition_variable c;
    
    TimePoint st, en;
    for (auto r = 0; r < 20; ++r)
    {
        std::unique_lock<std::mutex> lock(m);
        
        st = Clock::now();
        int i;
        for (i = 0; i < 10000000; ++i)
        {
            c.notify_all();
        }
        en = Clock::now();
        
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(en - st).count();
        
        std::cout << ns / i << std::endl;
    }
}
