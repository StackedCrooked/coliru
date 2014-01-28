#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <iterator>

int main()
{
    const double inf = 1.0 / 0.0 ;
    const double nan = 0.0 / 0.0 ;
    std::vector<double> data1 { 2.123, 2.111, 9.222, -5.6, 6.8, 0.0, nan } ;
    std::vector<double> data2 { 1.22, 4.33, 2.113, 0.0, 13.2, inf, nan } ;
    // 0 - infinity == -infinity, std::abs(-infinity) is +infinity
    // NaN - NaN == NaN
    
    // ...

    assert( data1.size() <= data2.size() ) ;

    {
        // algorithm (uses iterators): works with all sequence containers
        std::vector<double> result ;

        std::transform( std::begin(data1), std::end(data1),
                         std::begin(data2),
                         std::back_inserter(result),
                         []( double a, double b ) { return std::abs(a-b) ; } ) ;

        for( double d : result ) std::cout << d << ' ' ;
        std::cout << '\n' ;
    }

    {
        // subscript: works with sequence containers which support random access
        std::vector<double> result ;

        for( std::size_t i = 0 ; i < data1.size() ; ++i )
            result.push_back( std::abs( data1[i] - data2[i] ) ) ;

        for( double d : result ) std::cout << d << ' ' ;
        std::cout << '\n' ;
    }
}
