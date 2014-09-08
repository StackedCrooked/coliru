#include <memory>
#include <iostream>
#include <chrono>

using namespace std::chrono;

int main()
{
    auto start = system_clock::now();
    
    auto x = 0;
    for (auto i = 0; i < 100000000; ++i) { x += i % 2; }
    
    auto end = system_clock::now();
    
    auto elapsed_ms = duration_cast<milliseconds>(end - start).count();
    
    std::cout << "Time elapsed: " << elapsed_ms << " ms" << std::endl;
    
    // std::cout << "Value of x: " << x;
}