#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
    using namespace std::chrono ;
    std::srand( std::time(nullptr) ) ;
    
    constexpr std::size_t N = 1'000'000 ;
    constexpr std::size_t M = 32 ;
    
    std::vector<std::size_t> seq(N) ;
    //std::iota( std::begin(seq), std::end(seq), 0 ) ;
    
    double total_ms = 0 ;
    
    for( std::size_t i = 0 ; i < M ; ++i ) 
    {
        std::generate( std::begin(seq), std::end(seq), std::rand ) ;
        
        const auto start = std::clock() ;
        std::sort( std::begin(seq), std::end(seq) ) ;
        const auto end = std::clock() ;
        
        total_ms += ( double(end-start) * 1000 ) / CLOCKS_PER_SEC ; ;
    }
    
    std::cout << "average processor time to sort " << N << " integers: " << total_ms / M << " millisecs\n" ;
}
