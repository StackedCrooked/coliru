#include <iostream>
#include <iterator>
#include <algorithm>

int main ()
{
    const int N = 3 ;
    int a[N][4] = { {0,1,2,3}, {4,5,0,1}, {2,3,4,5} };

    for( const auto& row : a )
    {
        for( int v : row ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }
    std::cout << '\n' ;

    std::sort( std::begin( a[0] ), std::end( a[N-1] ) ) ;
    
    for( const auto& row : a )
    {
        for( int v : row ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }
    std::cout << '\n' ;
}
