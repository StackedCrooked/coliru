#include <iostream>
#include <thread>
#include <chrono>
#include <string>

class benchmark
{
public:
    benchmark(std::string const & name)
        : name(name)
        , start(std::chrono::high_resolution_clock::now())
    {
    }
    
    ~benchmark()
    {
        std::cout << "Thread \"" << name << "\" took "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count()
            << "ns" << std::endl;
    }
    
private:
    std::string name;
    std::chrono::high_resolution_clock::time_point start;
};

#define ENABLE_BENCHMARK(name) benchmark name##_benchmark(#name); ((void)name##_benchmark)

int main()
{
    std::thread foo([](){
        ENABLE_BENCHMARK(foo);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    });
    foo.join();
    return 0;
}
