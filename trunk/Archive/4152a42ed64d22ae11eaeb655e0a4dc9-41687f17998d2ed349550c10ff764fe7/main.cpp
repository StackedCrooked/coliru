#include <iostream>
#include <string>
#include <chrono>


#define STR_(S) #S
#define STR(S) STR_(S)


struct Stopwatch
{
    typedef std::chrono::high_resolution_clock Clock;
    Stopwatch() : start(Clock::now()) {}
    unsigned long elapsed() { return 100000u * (Clock::now() - start).count() / Clock::period::den; }
    Clock::time_point start;
};


std::string s = "1";


void test() THROW_SPEC 
{
    s.at(0);
}



int main()
{
    auto num_iterations = 1000000u;
    
    try
    {
        Stopwatch sw;
        for (unsigned i = 0; i != num_iterations; ++i) test();
        auto elapsed = sw.elapsed();
        std::cout << "using \"" << STR(THROW_SPEC) << "\": " << elapsed << std::endl;        
    }    
    catch (...)
    {
    }    
}