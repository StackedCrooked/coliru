#include <iostream>
#include <vector>

#include <chrono>
 
void a()
{
        // record start time
        auto start = std::chrono::high_resolution_clock::now();
        // do some work
        auto starttime = std::chrono::high_resolution_clock::now();
        auto since_epoch = std::chrono::high_resolution_clock::now();
        std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch-starttime).count();
        // record end time
        auto end = std::chrono::high_resolution_clock::now();
        //std::chrono::duration<long double> diff = end-start;
        //std::cout << diff.count() << " s\n";   
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << " s\n";
}


int main()
{
        // record start time
        auto start = std::chrono::high_resolution_clock::now();
        // do some work
        auto since_epoch = std::chrono::high_resolution_clock::now().time_since_epoch();
        std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch).count();
        // record end time
        auto end = std::chrono::high_resolution_clock::now();
        //std::chrono::duration<long double> diff = end-start;
        //std::cout << diff.count() << " s\n";
        
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << " s\n";
        a();
        
        
        
}
