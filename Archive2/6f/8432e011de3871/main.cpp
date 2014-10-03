#include <chrono>
#include <string>
#include <stdexcept>
#include <iostream>


// compiler must assume x may change by external party
volatile int x = 0;

int get_impl() { if (x != 0) throw std::runtime_error("x has changed"); return x; }

int get_noexcept() noexcept { return get_impl(); }
int get_normal() { return get_impl(); }



const int num_iterations = 10 * 1000 * 1000;


int test_inner_noexcept() 
{
    int result = 0;
    for (int i = 0; i != num_iterations; ++i)
    {
        result += get_noexcept(); // inner noexcept check
    }
    return result;
    
}


int test_outer_noexcept() noexcept // outer noexcept check
{
    int result = 0;
    for (int i = 0; i != num_iterations; ++i)
    {
        result += get_normal(); // no inner check
    }
    return result;
    
}


auto now = []{ return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); };


template<typename F>
void benchmark(const char* name, F&& f)
{
    auto start_time = now();
    auto result = f();
    auto elapsed_time = now() - start_time;
    std::cout << name << ": elapsed_time=" << elapsed_time << " (" << result << ")" << std::endl;
}
 

#define benchmark(f) benchmark(#f, f)


void run()
{
    benchmark(test_inner_noexcept);
    benchmark(test_inner_noexcept);
    benchmark(test_inner_noexcept);
    benchmark(test_inner_noexcept);
    std::cout << std::endl;
    
    benchmark(test_outer_noexcept);
    benchmark(test_outer_noexcept);
    benchmark(test_outer_noexcept);
    benchmark(test_outer_noexcept);
    std::cout << std::endl;
    
    benchmark(test_inner_noexcept);
    benchmark(test_inner_noexcept);
    benchmark(test_inner_noexcept);
    benchmark(test_inner_noexcept);
    std::cout << std::endl;
    
    benchmark(test_outer_noexcept);
    benchmark(test_outer_noexcept);
    benchmark(test_outer_noexcept);
    benchmark(test_outer_noexcept);
}

int main()
{
    try
    {
        run();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}