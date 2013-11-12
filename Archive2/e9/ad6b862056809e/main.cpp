#include <iostream>
#include <iostream>
#include <complex>
#include <memory>

template< typename T > std::ostream& foo_( T&& v )
{ return std::cout << v << ' ' ; }

template< typename FIRST, typename... REST >
std::ostream& foo_( FIRST&& first, REST&&... rest )
{
    foo_(first) ;
    return foo_(rest...) ;
}

template< typename... T > std::ostream& foo( T&&... args )
{ return foo_(args...) << '\n' ; }

int main()
{
    foo(1);
	foo(2, 3);
	std::complex<double> c { 4.5, 6.7 } ;
	foo( "hello", "world", 8, 9.012, c, std::addressof(c) ) ;
}
