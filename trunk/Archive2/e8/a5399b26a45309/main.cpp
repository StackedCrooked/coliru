#include <algorithm>
#include <chrono>
#include <iostream>


using Clock = std::chrono::steady_clock;

enum { array_size = 1000000 };


int main()
{

    uint8_t data[array_size];


    for (unsigned c = 0; c < array_size; ++c)
    {
        data[c] = std::rand() % 256;
    }


    long long sum = 0;


    auto t1 = Clock::now();

    // sort the data
    #if SORT
    std::sort(data, data + array_size);
    #endif

    auto t2 = Clock::now();

    for (unsigned c = 0; c < array_size; ++c)
    {
        if (data[c] % 3 == 0)
        {
            sum += data[c];
        }
    }

    auto t3 = Clock::now();

    auto sortTime = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    auto processingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(t3 - t2);
    auto totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(t3 - t1);

    std::cout
        << "Sort=" << (SORT ? "yes" : "no")
        << " SortTime=" << sortTime.count()
        << " ProcessingTime=" << processingTime.count()
        << " TotalTime=" << totalTime.count()
        << " (disable_optimization=" << sum << ")"
        << std::endl;
}
