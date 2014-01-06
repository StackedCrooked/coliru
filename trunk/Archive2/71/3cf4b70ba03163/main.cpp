#include <iostream>

template < std::size_t N >
void foo( char (&) [N] ) { std::cout << "array of char\n" ; }

template < std::size_t N >
void bar( char (&) [N] ) { std::cout << "overload for 'array of char'\n" ; }

template < std::size_t N >
void bar( const char (&) [N] ) { std::cout << "overload for 'array of const char'\n" ; }

int main ()
{
    // foo( "hello" ) ; // *** error: no matching function foo

    bar( "hello" ) ; // overload for 'array of const char'
}
