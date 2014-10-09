#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

int main()
{
    using namespace std::chrono ;
    
    const auto startp = std::clock() ;
    const auto startw = steady_clock::now() ;
    
    volatile double d = 0 ;
    for( int i = 0 ; i < 10000000 ; ++i ) d += 23.8 ;
    
    // assume that there is heavy contention for the processor and mid-way through our loop, 
    // the operating system gives the resource to other competing processes for 200 msecs
    std::this_thread::sleep_for( milliseconds(200) ) ;

    for( int i = 10000000 ; i < 20000000 ; ++i ) d += 23.8 ;

    const auto endw = steady_clock::now() ;
    const auto endp = std::clock() ;
    
    std::cout << "elapsed wall clock time: " << duration_cast<milliseconds>( endw - startw ).count() << " msecs\n" 
              << "elapsed processor time: " << double( endp - startp ) * 1000 / CLOCKS_PER_SEC << " msecs\n" ;
}
