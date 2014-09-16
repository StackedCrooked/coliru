#include <unordered_map>
#include <malloc.h>
#include <random>
#include <ctime>

int main()
{
    std::unordered_map< std::size_t, std::uintptr_t > test ;
    const std::size_t N = 1000000 ;
    
    std::mt19937 twister( std::time(nullptr) ) ;
    std::uniform_int_distribution<std::size_t> distr( 1, 1000000000 ) ;
    
    for( std::size_t i = 0 ; i < N ; ++i ) test[ distr(twister) ] = i ;
    malloc_stats() ;
}
