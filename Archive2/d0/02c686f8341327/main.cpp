#include <iostream>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>

template< typename T, std::size_t N, typename PREDICATE, typename FN >
void WHERE( T(&a)[N], PREDICATE if_, FN fn )
{ for( auto& e : a ) if( if_(e) ) e = fn(e) ; }

int main()
{
    int a[10] { 0, 1, -2, 3, -4, -5, 6, 7, -8, 9 };

    const auto print = [&a]
    { for( int i : a ) std::cout << i << ' ' ; std::cout << '\n' ; } ;
    using boost::phoenix::arg_names::arg1 ;

    WHERE( a, arg1<0, arg1=25 ) ; print() ;

    WHERE( a, arg1%3 == 0, arg1+=30 ) ; print() ;
}
