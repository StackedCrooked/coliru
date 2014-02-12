#include <stdexcept>
#include <iostream>
#include <chrono>


int no_exception(long& n)
{
    n += 1;
    if (n == 0xFFFFFFFF)
    {
        return 1;
    }
    return 0;
}


void with_exception(long& n)
{
    n += 1;
    if (n == 0xFFFFFFFF)
    {
        throw std::runtime_error("bla");
    }
}


using namespace std::chrono;
typedef high_resolution_clock Clock;
    
void a(long n)
{    
    auto start_time = Clock::now();
    
    for (auto i = 0ul; i != 1000UL * 1000UL * 1000UL; ++i)
    {
        if (no_exception(n))
        {
            return;
        }
    }
    
    auto elapsed = duration_cast<milliseconds>(Clock::now() - start_time).count();
    std::cout << "No exception: " << elapsed << std::endl;
}

void b(long n)
{    
    auto start_time = Clock::now();
    
    for (auto i = 0ul; i != 1000UL * 1000UL * 1000UL; ++i)
    {
        with_exception(n);
    }
    
    auto elapsed = duration_cast<milliseconds>(Clock::now() - start_time).count();
    std::cout << "With exception: " << elapsed << std::endl;
}


int main(int argc, char**)
{
    a(argc);
    b(argc);
    a(argc);
    b(argc);
}
