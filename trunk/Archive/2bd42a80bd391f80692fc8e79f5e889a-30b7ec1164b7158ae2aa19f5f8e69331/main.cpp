#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include "tbb/concurrent_queue.h"


namespace {


void test_unbounded_queue(uint32_t iteration_count)
{
    typedef std::chrono::high_resolution_clock Clock;
    using std::chrono::duration_cast;
    using std::chrono::nanoseconds;

    tbb::concurrent_queue<uint32_t> unbounded_queue;

    uint32_t verify = 0;

    Clock::time_point start_time, end_time;

    std::thread consumer_thread([&]
    {
        start_time = Clock::now();

        // Active polling (100% CPU usage)
        while (true)
        {
            uint32_t n;
            if (unbounded_queue.try_pop(n))
            {
                if (n == uint32_t(-1))
                {
                    end_time = Clock::now();
                    return;
                }
                verify += n;
            }
        }
    });

    for (unsigned i = 0; i != iteration_count; ++i)
    {
        unbounded_queue.push(1);
    }

    // stop the thread
    unbounded_queue.push(uint32_t(-1));
    consumer_thread.join();

    // verify the iteration count
    if (verify != iteration_count)
    {
        std::cout << "verify: " << verify << " != " << iteration_count << std::endl;
        return;
    }

    // print the results
    auto total_time_ns = duration_cast<nanoseconds>(end_time - start_time).count();
    auto cost_per_pop = total_time_ns / iteration_count;
    std::cout
        << "iterations: "
        << std::setw(6) << iteration_count
        << ", total time: "
        << std::setw(9) << total_time_ns << " ns"
        << ", average time: "
        << std::setw(5) << cost_per_pop << " ns"
        << std::endl;
}


void test_bounded_queue(uint32_t iteration_count)
{
    typedef std::chrono::high_resolution_clock Clock;
    using std::chrono::duration_cast;
    using std::chrono::nanoseconds;

    tbb::concurrent_bounded_queue<uint32_t> bounded_queue;

    uint32_t verify = 0;

    Clock::time_point start_time, end_time;

    std::thread consumer_thread([&]
    {
        start_time = Clock::now();

        while (true)
        {
            uint32_t n;
            bounded_queue.pop(n); // waits, no CPU usage
            if (n == uint32_t(-1))
            {
                end_time = Clock::now();
                return;
            }
            verify += n;
        }
    });

    for (unsigned i = 0; i != iteration_count; ++i)
    {
        bounded_queue.push(1);
    }

    // stop the thread
    bounded_queue.push(uint32_t(-1));
    consumer_thread.join();

    // verify the iteration count
    if (verify != iteration_count)
    {
        std::cout << "verify: " << verify << " != " << iteration_count << std::endl;
        return;
    }

    // print the results
    auto total_time_ns = duration_cast<nanoseconds>(end_time - start_time).count();
    auto cost_per_pop = total_time_ns / iteration_count;
    std::cout
        << "iterations: "
        << std::setw(6) << iteration_count
        << ", total time: "
        << std::setw(9) << total_time_ns << " ns"
        << ", average time: "
        << std::setw(5) << cost_per_pop << " ns"
        << std::endl;
}


const uint32_t min_iterations = 1u;
const uint32_t max_iterations = 128u * 1024u;


void test_bounded()
{
    std::cout << "Test bounded queue" << std::endl;
    for (uint32_t i = min_iterations; i <= max_iterations; i *= 2)
    {
        test_bounded_queue(i);
    }
    std::cout << std::endl;
}


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
    test_bounded();
    test_unbounded();
}
