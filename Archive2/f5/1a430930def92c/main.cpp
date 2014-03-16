#include <iostream>
#include <initializer_list>

template < typename T, typename U >
bool in( const T& value, const std::initializer_list<U>& set )
{
    for( auto& v : set ) if( v == value ) return true ;
    return false ;
}

int main()
{
    char ch ;
    std::cin >> ch ;

    if( in( ch, { 'Y', 'y', 'N', 'n' } ) ) std::cout << "ok\n" ;
    
    int i = 7 ;
    if( in( i, { 1, 3, 5, 7, 9 } ) ) std::cout << "ok\n" ;
    
}
