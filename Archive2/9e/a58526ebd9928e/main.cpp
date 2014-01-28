#include <ctime>
#include <iostream>

volatile double d = 0 ;
volatile int i = 0 ;

int main()
{
    {
        const auto start = std::clock() ;
        for( int i=0 ; i < 1024*1024*1024 ; ++i ) d += 0.01 ;
        const auto end = std::clock() ;
        std::cout << double(end-start) / CLOCKS_PER_SEC << " seconds.\n" ;
    }

    {
        const auto start = std::clock() ;
        for( int j=0 ; j < 1024*1024*1024 ; ++j ) i += 1 ;
        const auto end = std::clock() ;
        std::cout << double(end-start) / CLOCKS_PER_SEC << " seconds.\n" ;
    }
}
