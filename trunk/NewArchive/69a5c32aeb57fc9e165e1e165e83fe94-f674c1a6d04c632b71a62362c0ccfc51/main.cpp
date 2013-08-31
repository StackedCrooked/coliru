#include <chrono>
#include <iostream>


class Stopwatch
{
public:
    typedef std::chrono::high_resolution_clock Clock;

    //! Constructor starts the stopwatch
    Stopwatch() : mStart(Clock::now())
    {
    }

    //! Returns elapsed number of seconds in decimal form.
    std::chrono::nanoseconds elapsed()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - mStart);
    }

    Clock::time_point mStart;
};


int main()
{
    Stopwatch sw;    
    const unsigned count=1000;
    
    
    for(unsigned i=0; i<10; ++i)
        std::cout << i << ' '; //warmup
    auto start = sw.elapsed().count();
    for(unsigned i=0; i<count; ++i)
        std::cout << i << ' ';
    auto end = sw.elapsed().count();
    auto noflush_diff = end - start;
    
    for(unsigned i=0; i<10; ++i)
        std::cout << i << ' ' << std::flush; //warmup
    start = sw.elapsed().count();
    for(unsigned i=0; i<count; ++i)
        std::cout << i << ' ' << std::flush;
    end = sw.elapsed().count();
    auto flush_diff = end - start;
    
    std::cout << "\nNo flushing: " << noflush_diff << "ns total, " << (double(noflush_diff)/count) << "ns average";
    std::cout << "\nFlushing   : " << flush_diff << "ns total, " << (double(flush_diff)/count) << "ns average";
}