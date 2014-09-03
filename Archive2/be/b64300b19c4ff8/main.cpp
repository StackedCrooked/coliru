#include <iostream>
#include <type_traits>

struct A { friend void foo( A ) { std::cout << "foo in scope of A\n" ; } } ;
struct B { friend void foo( B ) { std::cout << "foo in scope of B\n" ; } } ;

template < typename T > typename std::enable_if< std::is_base_of< A, T >::value >::type bar( T& )
{ std::cout << "bar for types derived from A\n" ; }

template < typename T > typename std::enable_if< std::is_base_of< B, T >::value >::type bar( T& )
{ std::cout << "bar for types derived from B\n" ; }

int main()
{
    struct C : A {} c ; foo(c) ; bar(c) ;
    struct D : B {} d ; foo(d) ; bar(d) ;

    struct AB : A, B {} ab ;
    // foo(ab) ; // *** error: ambiguous
    // bar(ab) ; // *** error: ambiguous
    foo( (B&)ab ) ; // fine
    bar( (A&)ab ) ; // fine
}
