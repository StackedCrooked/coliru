#include <iostream>
#include <vector>
#include <list>
#include <numeric>
#include <ctime>
#include <cassert>

volatile std::size_t n = 0 ;

template< typename CONTAINER > std::clock_t perf_size()
{
    constexpr std::size_t N = 16'000'000 ; 
    CONTAINER cntr(N) ;
    const auto start = std::clock() ;
    n = cntr.size() ;
    return std::clock() - start ;
}

int main()
{
    std::cout << "vector size: " << perf_size< std::vector<char> >() * 1000.0 / CLOCKS_PER_SEC << " msecs\n" ;
    std::cout << "list size: " << perf_size< std::list<char> >() * 1000.0 / CLOCKS_PER_SEC << " msecs\n" ;
}
