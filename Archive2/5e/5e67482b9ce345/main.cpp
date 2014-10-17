#include <iostream>
#include <vector>
#include <list>
#include <numeric>
#include <ctime>
#include <cassert>

template< typename CONTAINER > std::clock_t geminate( CONTAINER& cntr )
{
    const auto start = std::clock() ;
    for( auto iter = cntr.begin() ; iter != cntr.end() ; ++iter, ++iter )
        iter = cntr.insert( iter, *iter ) ;
    return std::clock() - start ;
}

int main()
{
    constexpr std::size_t N = 150'000 ; 
    
    {
        std::vector<int> vector(N) ;
        std::iota( std::begin(vector), std::end(vector), 0 ) ;
        vector.reserve( N*2 ) ;
        std::cout << "vector insert: " << geminate(vector) * 1000.0 / CLOCKS_PER_SEC << " msecs\n" ;
        assert( vector.size() == N*2 ) ;
    }
    
    {
        std::list<int> list(N) ;
        std::iota( std::begin(list), std::end(list), 0 ) ;
        std::cout << "list insert: " << geminate(list) * 1000.0 / CLOCKS_PER_SEC << " msecs\n" ;
        assert( list.size() == N*2 ) ; 
    }
}
