#include <iostream>
#include <chrono>
#include <unistd.h>
#include <stdint.h>


using namespace std::chrono;
typedef high_resolution_clock Clock;

template<typename Duration>
int64_t calculate_max_size(Duration duration, double max_bytes_per_second)
{
    double duration_seconds = std::chrono::duration_cast<Duration>(seconds(1)).count();
    return duration.count() * max_bytes_per_second / duration_seconds;
}


int main()
{
    std::cout << calculate_max_size(seconds(1), 1) << std::endl;
    std::cout << calculate_max_size(seconds(1), 2) << std::endl;
    std::cout << calculate_max_size(seconds(2), 1) << std::endl;
    std::cout << calculate_max_size(milliseconds(1), 1) << std::endl;
    std::cout << calculate_max_size(milliseconds(1), 1000) << std::endl;
    std::cout << calculate_max_size(milliseconds(1), 1000000) << std::endl;
}
//
//
//struct RateLimiter
//{
//    
//    RateLimiter(double inRateLimit) :
//        mRateLimit(inRateLimit),
//        mLastTime(Clock::now())
//    {
//    }
//    
//    int64_t get(Clock::time_point current_time) const
//    {
//        double elapsed_seconds = duration_cast<microseconds>(current_time - mLastTime).count() / 1000000.0;
//        auto result = mRateLimit * elapsed_seconds;        
//        mLastTime = current_time;
//        return result;
//    }
//    
//    double mRateLimit; // bytes/second
//    mutable Clock::time_point mLastTime;
//};
//
//
//
//
//int main()
//{
//    RateLimiter rate_limiter(1000);
//    
//    auto start_time = Clock::now();
//    auto elapsed_seconds = [&](Clock::time_point current_time)
//    {
//        return int64_t(0.5 + 1000.0 * duration_cast<microseconds>(current_time - start_time).count() / 1000000) / 1000.0;
//    };
//    
//    
//    int64_t total = 0;
//    for (int i = 0; i != 20; ++i)
//    {
//        auto current_time = Clock::now();
//        auto rate_limit = rate_limiter.get(current_time);
//        auto elapsed_s = elapsed_seconds(current_time);
//        total += rate_limit;
//        
//        std::cout
//            << elapsed_s
//            << " rate_limit=" << rate_limit
//            << " total=" << total
//            << '\n'
//            ;
//        usleep(200 * 1000);
//    }
//}