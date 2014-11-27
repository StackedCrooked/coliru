#include <iostream>
#include <unordered_map>
#include <random>
#include <ctime>

std::vector<long long> make_data_set( long long minv = -9'999'999'999'999'999, long long maxv = +9'999'999'999'999'999, std::size_t N = 1'000'000 )
{
    static std::mt19937 rng( std::time(nullptr) ) ;
    
    std::uniform_int_distribution<int> distrib( minv, maxv ) ;
    std::vector<long long> result ;
    while( result.size() < N ) result.push_back( distrib(rng) ) ;
    return result ;
}

constexpr std::pair< std::size_t, std::size_t > NOT_FOUND { -1U, -1U } ;

std::pair< std::size_t, std::size_t > find_matching_pair( const std::vector<long long>& seq, long long sum )
{
    std::unordered_map< long long, std::size_t > map ;
    
    for( std::size_t i = 0 ; i < seq.size() ; ++i )
    {
        const auto iter = map.find( sum - seq[i] ) ;
        if( iter != map.end() ) return { i, iter->second } ;
        else map[ seq[i] ] = i ;
    }
    
    return NOT_FOUND ;
}

int main()
{
    const auto data = make_data_set() ;
    
    for( int i=0 ; i<5 ; ++i )
    {
        const auto target = i * 1'000'000'000LL ;
    
        const auto p = find_matching_pair( data, target ) ; 

        if( p != NOT_FOUND )
        {
            std::cout << "found: " << data[p.first] << " at position " << p.first << " && "
                      << data[p.second] << " at position " << p.second << '\n'
                      << data[p.first] << " + " << data[p.second] << " == " << data[p.first] + data[p.second] << "\n\n" ;
        }
        
        else std::cout << "did not find numbers summing up to " << target << '\n' ;
    }
}
