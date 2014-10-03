#include <chrono>
#include <string>
#include <stdexcept>
#include <iostream>


// compiler must assume x may change by external party
volatile int x = 0;

int get_impl() { if (x != 0) throw std::runtime_error("x has changed"); return x; }

int get1() noexcept { return get_impl(); }
int get2() { return get_impl(); }



const int num_iterations = 1000 * 1000;


int test1()
{
    int result = 0;
    for (int i = 0; i != num_iterations; ++i)
    {
        result += get1(); // no inner noexcept
    }
    return result;
    
}


int test2()
{
    int result = 0;
    for (int i = 0; i != num_iterations; ++i)
    {
        result += get2(); // inner noexcept
    }
    return result;
    
}


auto now = []{ return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); };


template<typename F>
void benchmark(const char* name, F&& f)
{
    try
    {
        auto start_time = now();
        auto result = f();
        auto elapsed_time = now() - start_time;
        std::cout << name << ": elapsed_time=" << elapsed_time << "ns (" << result << ")" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught exception: " << e.what();
    }
}
 

#define benchmark(f) benchmark(#f, f)


int main()
{
    benchmark(test1);
    benchmark(test1);
    benchmark(test1);
    benchmark(test1);
    std::cout << std::endl;
    
    benchmark(test2);
    benchmark(test2);
    benchmark(test2);
    benchmark(test2);
    std::cout << std::endl;
    
    benchmark(test1);
    benchmark(test1);
    benchmark(test1);
    benchmark(test1);
    std::cout << std::endl;
    
    benchmark(test2);
    benchmark(test2);
    benchmark(test2);
    benchmark(test2);
}
