#include <iostream>
#include <random>
#include <ctime>
#include <valarray>
#include <vector>
#include <numeric>
#include <algorithm>

template < std::size_t N > double foo( double (&a)[N], const double (&b)[N], const double (&c)[N], double d )
{
    for( std::size_t i = 0 ; i < N ; ++i )
        a[i] = d * b[i] + c[i] ;
    return std::accumulate( a, a+N, 0.0 ) ;
}

double foo( std::valarray<double>& a, const std::valarray<double>& b, const std::valarray<double>& c, double d )
{
    a = d * b + c ;
    return a.sum() ;
}

double foo( std::vector<double>& a, const std::vector<double>& b, const std::vector<double>& c, double d )
{
    for( std::size_t i = 0 ; i < a.size() ; ++i )
        a[i] = d * b[i] + c[i] ;
    return std::accumulate( a.begin(), a.end(), 0.0 ) ;
}

int main()
{
    const std::size_t N = 1024 * 1024 * 12 ;
    std::mt19937 rng( std::time(nullptr) ) ;
    std::normal_distribution<double> distrib( 1, 0.5 ) ;
    const auto rand = [&] { return distrib(rng) ; };
    double d = rand() ;
    double n = 0.0 ;

    static double a[N], b[N], c[N] ;
    std::generate_n( a, N, rand ) ;
    std::generate_n( b, N, rand ) ;
    std::generate_n( c, N, rand ) ;

    {
        const auto start = std::clock() ;
        n += foo( a, b, c, d ) ;
        const auto end = std::clock() ;
        std::cout << "array: " << (end-start) * 1000.0 / CLOCKS_PER_SEC << " msecs.\n" ;
    }

    {
        std::vector<double> aa( a, a+N ), bb( b, b+N ), cc( c, c+N ) ;

        const auto start = std::clock() ;
        n += foo( aa, bb, cc, d ) ;
        const auto end = std::clock() ;
        std::cout << "vector: " << (end-start) * 1000.0 / CLOCKS_PER_SEC << " msecs.\n" ;
    }

    {
        std::valarray<double> aa( a, N ), bb( b, N ), cc( c, N ) ;

        const auto start = std::clock() ;
        n += foo( aa, bb, cc, d ) ;
        const auto end = std::clock() ;
        std::cout << "valarray: " << (end-start) * 1000.0 / CLOCKS_PER_SEC << " msecs.\n" ;
    }

    std::cout << n << '\n' ;

}
