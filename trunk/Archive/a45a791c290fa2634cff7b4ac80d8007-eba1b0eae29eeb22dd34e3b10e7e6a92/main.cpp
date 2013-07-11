#include "tbb/concurrent_queue.h"
#include <boost/optional.hpp>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>


namespace {


void test_unbounded_queue(uint32_t iteration_count)
{
    typedef std::chrono::high_resolution_clock Clock;
    using std::chrono::duration_cast;
    using std::chrono::nanoseconds;

    tbb::concurrent_queue<uint32_t> unbounded_queue;

    uint32_t verify = 0;

    boost::optional<Clock::time_point> start_time;
    Clock::time_point end_time{};

    std::thread([&]
    {
        unbounded_queue.push(1);

        // Active polling (100% CPU usage)
        while (true)
        {
            uint32_t n;
            if (unbounded_queue.try_pop(n))
            {
                if (!start_time)
                {
                    start_time.reset(Clock::now());
                    std::thread([&]{
                        for (unsigned i = 1; i != iteration_count; ++i)
                        {
                            unbounded_queue.push(1);
                        }
                        unbounded_queue.push(uint32_t(-1));
                    }).detach();
                }
                if (n == uint32_t(-1))
                {
                    end_time = Clock::now();
                    return;
                }
                verify += n;
            }
        }
    }).join();

    // stop the thread
    

    // verify the iteration count
    if (verify != iteration_count)
    {
        std::cout << "verify: " << verify << " != " << iteration_count << std::endl;
        return;
    }

    // print the results
    auto total_time_ns = duration_cast<nanoseconds>(end_time - start_time.get()).count();
    auto cost_per_pop = total_time_ns / iteration_count;
    std::cout
        << "iterations: "
        << std::setw(10) << iteration_count
        << ", total time: "
        << std::setw(10) << total_time_ns << " ns"
        << ", average time: "
        << std::setw(10) << cost_per_pop << " ns"
        << std::endl;
}


const uint32_t min_iterations = 16777216u;
const uint32_t max_iterations = 1024u * 1024u * 1024u;


void test_unbounded()
{
    std::cout << "Test unbounded queue" << std::endl;
    for (uint32_t i = min_iterations; i <= max_iterations; i *= 2)
    {
        test_unbounded_queue(i);
    }
    std::cout << std::endl;
}


} // namespace


int main()
{
    test_unbounded();
}
