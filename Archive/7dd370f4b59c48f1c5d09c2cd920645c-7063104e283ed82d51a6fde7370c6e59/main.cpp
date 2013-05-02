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
    double minimum_cost = 10000;
    Stopwatch sw_total;
    for (int i = 0; i != 1000; ++i)
    {
        Stopwatch sw;
        std::thread([]{}).join();
        auto time = std::min(minimum_cost, sw.elapsed());
        if (time != minimum_cost)
        {
            std::cout << std::fixed << time << std::endl;
            minimum_cost = time;
        }
        
    }
    
    auto average_cost = (1000000 * sw_total.elapsed() / 1000);
    std::cout << "Average cost of thread creation + destruction: " << std::fixed << average_cost << " microseconds" << std::endl;
    std::cout << "Minimum cost of thread creation + destruction: " << std::fixed << (1000000 * minimum_cost) << " microseconds" << std::endl;
}