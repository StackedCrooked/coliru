#include <iostream>

template < typename T, std::size_t N >
void foo( T (&reference_to_array)[N] ) // pass array by reference
{
    for( T& v : reference_to_array ) ++v ;
}

template < typename T, std::size_t N >
void bar( T (*pointer_to_array)[N] ) // pass pointer to array
{
    if( pointer_to_array != nullptr ) for( T& v : *pointer_to_array ) ++v ;
}


template < typename POINTER >
void baz( POINTER pointer_to_first_element[], std::size_t n ) // pass pointer to first element and size
{
    if( pointer_to_first_element != nullptr )
        for( std::size_t i = 0 ; i < n ; ++i ) ++pointer_to_first_element[i] ;
}

template < typename POINTER >
void foobar( POINTER begin, POINTER end ) // pass pair of iterators
{
    for( ; begin != end ; ++begin ) ++ *begin ;
}

int main()
{
    const std::size_t N = 5 ;
    int a[N] = { 0, 1, 2, 3, 4 } ;
    const auto print = [&a] { for( int v : a ) std::cout << v << ' ' ; std::cout << '\n' ; } ;

    print() ;

    foo(a) ; print() ;

    bar( &a ) ; print() ;

    baz( a, N ) ; print() ;

    foobar( a, a+N ) ; print() ;
}
