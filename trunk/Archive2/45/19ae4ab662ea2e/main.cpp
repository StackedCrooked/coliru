#include <vector>
#include <memory>
#include <ctime>
#include <iostream>


int foo( const std::vector<int>& vector ) ;
int foo( const int carray[], std::size_t size ) ;

int main()
{
    constexpr std::size_t N = 1024*1024*32 ;
    constexpr std::size_t M = 32 ;
    
    int a = 0 ;
    {
        std::vector<int> seq(N) ;
        const auto start = std::clock() ;
        for( std::size_t i = 0 ; i < M ; ++i ) a += foo(seq) ;
        const auto end = std::clock() ;
        std::cout << "vector: " << ( end - start ) / double(CLOCKS_PER_SEC) * 1000 << " millisecs.\n" ;
    }
        
    int b = 0 ;
    {
        std::unique_ptr< int[] > carray( new int[N]{} ) ;
        const auto start = std::clock() ;
        for( std::size_t i = 0 ; i < M ; ++i ) b += foo( carray.get(), N ) ;
        const auto end = std::clock() ;
        std::cout << "carray: " << ( end - start ) / double(CLOCKS_PER_SEC) * 1000 << " millisecs.\n" ;
    }

    return a + b ;
}

