#include <iostream>
#include <string>
#include <thread>


class Stopwatch
{
public:
    typedef std::chrono::high_resolution_clock Clock;

    //! Constructor starts the stopwatch
    Stopwatch() : mStart(Clock::now())
    {
    }

    //! Returns elapsed number of seconds in decimal form.
    double elapsed()
    {
        return 1.0 * (Clock::now() - mStart).count() / Clock::period::den;
    }

    Clock::time_point mStart;
};


int main()
{
    double min_time = 1;
    for (int i = 0; i != 1000; ++i)
    {
        Stopwatch sw;
        std::thread([]{}).join();
        auto time = std::min(min_time, sw.elapsed());
        if (time != min_time)
        {
            std::cout << std::fixed << time << std::endl;
            min_time = time;
        }
        
    }
    std::cout << "Cost of thread creation + destruction: " << std::fixed << (1000000 * min_time) << " microseconds" << std::endl;
}