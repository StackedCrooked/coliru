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
    auto prev = sw.elapsed().count();
    std::cout << "No flushing: ";
    for (int i = 0; i != 20; ++i) {
        auto cur = sw.elapsed().count();
        auto diff = (cur - prev)/100;
        std::cout << diff << '\t';
        prev = cur;
    }
    
    std::cout << std::endl;
    
    std::cout << "Flushing   : ";
    for (int i = 0; i != 20; ++i) {
        auto cur = sw.elapsed().count();
        auto diff = (cur - prev)/100;
        std::cout << diff << '\t' << std::flush;
        prev = cur;
    }
}