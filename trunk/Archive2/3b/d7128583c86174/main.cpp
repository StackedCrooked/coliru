#include <iostream>
#include <iomanip>
#include <string>
#include <numeric>
#include <iterator>

template < typename T, std::size_t A, std::size_t B, std::size_t C >
using array_3d = T[A][B][C] ;

template < typename T, std::size_t A, std::size_t B, std::size_t C >
std::ostream& operator<< ( std::ostream& stm, const array_3d<T,A,B,C>& a3d )
{
    const int width = stm.width() ;
    const char fill = stm.fill() ;
    int spacer = width ;

    for( const auto& a2d : a3d )
    {
        for( const auto& row : a2d )
        {
            std::cout << std::string( spacer, ' ' ) ;
            for( const T& v : row ) stm << std::setw(width) << std::setfill(fill) << v << ' ' ;
            stm << '\n' ;
        }
        std::cout << '\n' ;
        spacer += width + 1 ;
    }

    return stm ;
}

int main()
{
    int a[3][4][5] ;
    std::iota( std::begin( a[0][0] ), std::end( a[2][3] ), 0 ) ;

    std::cout << "the array contains:\n\n" << std::setw(3) << a << '\n' ;
}
