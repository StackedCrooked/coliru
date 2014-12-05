#include <iostream>
#include <cmath>
#include <numeric>
#include <ctime>

template < typename T, std::size_t N > std::clock_t test( T (&a)[N], T& v )
{
    const auto start = std::clock() ;

    std::fill( a, a+N, 1 ) ;
    for( std::size_t i = 0 ; i < N ; ++i )
    {
        a[i] += std::sin( a[i] ) ;
        a[i] *= ( 1 + std::sqrt( a[i] ) ) ;
        a[i] -= std::cos( a[i] ) ;
        a[i] = std::abs(a[i]) ;
        a[i] += std::log( a[i] ) ;
        a[i] *= ( 1 + std::sqrt( a[i] ) ) ;
        a[i] += std::lgamma( a[i] ) ;
    }

    v = std::accumulate( a, a+N, 0 ) ;

    return std::clock() - start ;
}

int main()
{
    constexpr std::size_t N = 1024*1024*4 ;

    {
        static float f[N] ;
        float v ;
        std::cout << "float: " << test(f,v) * 1000 / CLOCKS_PER_SEC << " millisecs\n" ; 
    }

    {
        static double d[N] ;
        double v ;
        std::cout << "double: " << test(d,v) * 1000 / CLOCKS_PER_SEC << " millisecs\n" ; 
    }
}
