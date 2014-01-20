#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
 
// the function f() does some time-consuming work
void f()
{
    volatile double d;
    d = 0;
    for(int n=0; n<10000; ++n)
       for(int m=0; m<10000; ++m)
           d += d*n*m;
}
 
int main()
{
    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();
    std::thread t1(f); 
    std::thread t2(f); // f() is called on two threads
    t1.join();
    t2.join();
    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();
 
    std::cout << "CPU time used: "
              << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC
              << " ms\n";
    std::cout << "Wall clock time passed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
              << " ms\n";
}