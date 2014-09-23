#include <iostream>
#include <type_traits>

template < typename T > void foo( T&& )
{
    if( std::is_same< T, int >::value ) std::cout << "int\n" ;
    else if( std::is_same< T, int& >::value ) std::cout << "int&\n" ;
    else if( std::is_same< T, const int& >::value ) std::cout << "const int&\n" ;
}

int main()
{
    foo(100) ; // int
    int i = 45 ; foo(i) ; // int&
    const int j = 7 ; foo(j) ; // const int&
}
