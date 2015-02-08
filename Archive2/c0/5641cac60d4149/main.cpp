#include <iostream>
#include <random>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <ctime>

std::string rand_str( std::size_t n = 40 )
{
    static std::mt19937 rng( std::random_device{}() ) ;
    static std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" ;

    std::shuffle( std::begin(alphabet), std::end(alphabet), rng ) ;
    return alphabet.substr( 0, n ) ;
}

int cnt = 0 ;

template < typename MAP_TYPE >
std::clock_t test( const std::vector< typename MAP_TYPE::key_type >& keys,
                   const std::vector< typename MAP_TYPE::mapped_type >& values )
{
    const auto start = std::clock() ;

    const auto n = std::min( keys.size(), values.size() ) ;
    MAP_TYPE map ;
    for( std::size_t i = 0 ; i < n ; ++i ) map.emplace( keys[i], values[i] ) ;

    extern int cnt ;
    for( const auto& key : keys ) cnt += map.find(key) != map.end() ;

    return std::clock() - start ;
}

int main()
{
    constexpr std::size_t N = 1024*1024 ;

    std::vector<std::string> keys ;
    while( keys.size() < N ) keys.push_back( rand_str() ) ;
    std::vector<int> values(N/2) ;

    const auto ticks_m = test< std::map<std::string,int> >( keys, values ) ;
    std::cout << "          map: " << ticks_m * 1000.0 / CLOCKS_PER_SEC << " millisecs.\n" ;

    const auto ticks_um = test< std::unordered_map<std::string,int> >( keys, values ) ;
    std::cout << "unordered_map: " << ticks_um * 1000.0 / CLOCKS_PER_SEC << " millisecs.\n" ;
}
