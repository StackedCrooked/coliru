#include <iostream>
#include <set>
#include <cassert>
#include <ctime>

template < typename T, typename U >
void merge( std::set<T>& larger, const std::set<U>& smaller )
{
    assert( *smaller.rbegin() < *larger.begin() ) ;
    for( auto iter = smaller.rbegin() ; iter != smaller.rend() ; ++iter ) 
        larger.emplace_hint( larger.cbegin(), *iter ) ;
}

struct timer
{
    ~timer()
    {
        auto end = std::clock() ;
        std::cout << double( end - begin ) / CLOCKS_PER_SEC << " secs.\n" ;
    };

    const std::clock_t begin = std::clock() ;
};

void time_it( std::size_t n )
{
    std::set<int> smaller ;
    std::set<double> larger ;
    for( std::size_t i = 0 ; i < n ; ++i )
    {
        smaller.emplace_hint( smaller.cend(), i ) ;
        larger.emplace_hint( larger.cend(), i+n ) ;
    }
    std::cout << "n == " << n << "  " ;
    {
        timer t ;
        merge( larger, smaller ) ;
    }
    assert( larger.size() == n*2 ) ;
}

int main ()
{
    std::size_t n = 256 * 1024 ;
    for( int i = 0 ; i < 5 ; ++i )
    {
        time_it(n) ;
        n *= 2 ;
    }
}
