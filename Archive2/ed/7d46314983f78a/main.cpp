#include <iostream>

template< typename T, std::size_t N, typename PREDICATE >
void WHERE( T(&a)[N], PREDICATE fn, const T& v )
{ for( auto& e : a ) if( fn(e) ) e = v ; }

int main()
{
    int a[10] { 0, 1, -2, 3, -4, -5, 6, 7, -8, 9 };

    const auto negative = []( int i ) { return i<0 ; } ;
    WHERE( a, negative, 25 ) ;

    for( int i : a ) std::cout << i << ' ' ;
    std::cout << '\n' ;
}
