#include <iostream>
#include <unordered_map>
#include <random>
#include <ctime>

std::vector<int> make_data_set( int minv = 1'000'000, int maxv = 2'000'000'000, std::size_t N = 1'000'000 )
{
    static std::mt19937 rng( std::time(nullptr) ) ;
    std::uniform_int_distribution<int> distrib( minv, maxv ) ;
    std::vector<int> result ;
    while( result.size() < N ) result.push_back( distrib(rng) ) ;
    return result ;
}

constexpr std::pair< std::size_t, std::size_t > NOT_FOUND { -1U, -1U } ;

std::pair< std::size_t, std::size_t > find_matching_pair( const std::vector<int>& seq, int sum )
{
    std::unordered_map< int, std::size_t > map ;
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
    const auto p = find_matching_pair( data, 200'000'000 ) ; // sums up to 200000000
    if( p != NOT_FOUND )
    {
        std::cout << "found: " << data[p.first] << " at position " << p.first << " &&\n"
                  << data[p.second] << " at position " << p.second << '\n'
                  << data[p.first] << " + " << data[p.second] << " == " << data[p.first] + data[p.second] << '\n' ;
    }
}
