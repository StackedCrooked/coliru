#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <algorithm>

struct cpu_timer
{
    ~cpu_timer()
    {
        auto end = std::clock() ;
        std::cout << double( end - begin ) / CLOCKS_PER_SEC << " secs.\n" ;
    };

    const std::clock_t begin = std::clock() ;
};

int main()
{
    constexpr int N = 128 ;
    static volatile std::size_t a[N] ;

    constexpr int M = 1024*1024 ;

    std::srand( std::time(nullptr) ) ;

    {
        std::cout << "std::iota: " ;
        cpu_timer timer ;
        for( int i = 0 ; i < M ; ++i ) std::iota( a, a+N, 0 ) ;
    }

    {
        std::cout << "std::random_shuffle: " ;
        cpu_timer timer ;
        for( int i = 0 ; i < M ; ++i ) std::random_shuffle( a, a+N ) ;
    }

    {
        std::cout << "std::shuffle (mt19937): " ;
        std::mt19937 twister( std::time(nullptr) ) ;
        cpu_timer timer ;
        for( int i = 0 ; i < M ; ++i ) std::shuffle( a, a+N, twister ) ;
    }
}
