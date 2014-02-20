#include <thread>
#include <chrono>
#include <iostream>

int main()
{
    std::cout << "begin wait (800 microseconds)\n" << std::flush ;
    auto t1 = std::chrono::high_resolution_clock::now() ;
    
    // wait until at least 800 microseconds have passed.
    std::this_thread::sleep_for( std::chrono::microseconds(800) );
    
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "waited for " << std::fixed
              << std::chrono::duration_cast<std::chrono::nanoseconds>( (t2-t1) ).count() / 1000.0
              << " microseconds.\n\n" << std::flush ;
    
    std::cout << "begin wait (3.5 seconds)\n" << std::flush ;
    auto t3 = std::chrono::steady_clock::now() ;

    // wait until at least 3.5 seconds have passed.
    std::this_thread::sleep_for( std::chrono::milliseconds(3500) );
    
    auto t4 = std::chrono::steady_clock::now() ;
    std::cout << "waited for " << std::fixed
              << std::chrono::duration_cast<std::chrono::microseconds>( (t4-t3) ).count() / 1000000.0
              << " seconds.\n\n" << std::flush ;
}
