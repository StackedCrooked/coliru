#include <iostream>
#include <string>
#include <chrono>

struct Stopwatch {
    typedef std::chrono::high_resolution_clock Clock;
    Stopwatch() : mStart(Clock::now())     {     }

    //! Returns elapsed number of seconds in decimal form.
    double elapsed() { return 1.0 * (Clock::now() - mStart).count() / Clock::period::den; }

    Clock::time_point mStart;
};


void test() THROW_SPEC
{
    delete new char;
}

#define STR_(S) #S
#define STR(S) STR_(S)

int main()
{
    auto num_iterations = 40000000u;
    
    try
    {
        Stopwatch sw;
        for (unsigned i = 0; i != num_iterations; ++i) test();
        auto elapsed = sw.elapsed();
        std::cout << "Using: \"" << STR(THROW_SPEC) << "\": " << elapsed << std::endl;
    }    
    catch (...)
    {
    }    
}