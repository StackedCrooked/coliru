#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include <set>
#include <ctime>
#include <map>
#include <iostream>

std::string random_string( std::mt19937& twister )
{
    static std::uniform_int_distribution<std::size_t> rand_size(10,100) ;
    static std::uniform_int_distribution<char> rand_char_distr( 1, 127 ) ;
    const auto rand_char = [&twister] { return rand_char_distr(twister) ; };

    std::string str( rand_size(twister), 0 ) ;
    std::generate( str.begin(), str.end(), rand_char ) ;
    return str ;
}

std::vector< std::pair<std::size_t,std::string> >
                      generate_data( std::mt19937& twister, std::size_t n )
{
    std::set< std::pair<std::size_t,std::string> > s ;
    while( s.size() < n ) s.emplace( twister(), random_string(twister) ) ;

    std::vector< std::pair<std::size_t,std::string> > v( s.begin(), s.end() ) ;
    std::shuffle( v.begin(), v.end(), twister ) ;
    return v ;
}

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
    std::mt19937 rng( std::time(nullptr) ) ;
    constexpr std::size_t N = 1024 * 512 ;
    const auto test_data = generate_data( rng, N ) ;
    std::size_t cnt ;

    {
        std::cout << "map with key == int : " ;
        std::map< std::size_t, std::string > m ;
        cpu_timer t ;
        for( const auto& p : test_data ) m.emplace( p.first, p.second ) ;
        for( const auto& p : test_data ) m.emplace( p.first, p.second ) ; // duplicates

        cnt = 0 ;
        for( const auto& p : test_data ) if( m.find(p.first) != m.end() ) ++cnt ; // look up
    }
    std::cout << "cnt: " << cnt << '\n' ;

    {
        std::cout << "map with key == string: " ;
        std::map< std::string, std::size_t > m ;
        cpu_timer t ;
        for( const auto& p : test_data ) m.emplace( p.second, p.first ) ;
        for( const auto& p : test_data ) m.emplace( p.second, p.first ) ; // duplicates

        cnt = 0 ;
        for( const auto& p : test_data ) if( m.find(p.second) != m.end() ) ++cnt ; // look up
    }
    std::cout << "cnt: " << cnt << '\n' ;
}
