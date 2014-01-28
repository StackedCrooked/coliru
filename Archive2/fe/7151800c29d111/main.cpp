#include <ctime>
#include <iostream>
#include <atomic>

volatile double d = 0 ;
volatile long long i = 0 ;
std::atomic<int> atomic_i(0) ;

int main()
{
    constexpr int N = 1024*1024*256 ;
    
    {
        const auto start = std::clock() ;
        for( int i=0 ; i < N ; ++i ) d += 0.01 ;
        const auto end = std::clock() ;
        std::cout << "volatile double: " << double(end-start) / CLOCKS_PER_SEC << " seconds.\n" ;
    }

    {
        const auto start = std::clock() ;
        for( int j=0 ; j < N ; ++j ) i += 1 ;
        const auto end = std::clock() ;
        std::cout << "volatile int: " << double(end-start) / CLOCKS_PER_SEC << " seconds.\n" ;
    }

    {
        const auto start = std::clock() ;
        for( int j=0 ; j < N ; ++j ) atomic_i.fetch_add( 1, std::memory_order_relaxed ) ;
        const auto end = std::clock() ;
        std::cout << "fenced int (relaxed): " << double(end-start) / CLOCKS_PER_SEC << " seconds.\n" ;
    }

    {
        const auto start = std::clock() ;
        for( int j=0 ; j < N ; ++j ) atomic_i += 1 ;
        const auto end = std::clock() ;
        std::cout << "fenced int (sequentially consistent): " << double(end-start) / CLOCKS_PER_SEC << " seconds.\n" ;
    }
}
