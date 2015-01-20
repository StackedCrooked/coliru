#include <utility>
#include <typeindex>

template < typename T > struct result : std::pair< T, std::type_index >
{ result( T v ) : std::pair< T, std::type_index >( v, typeid(v) ) {} };

template < typename... > struct type_selector ;

template < typename T > struct type_selector<T>
{ static  result<T> select( T v ) { return v ; } };

template < typename FIRST, typename... REST > struct type_selector<FIRST, REST...>
{
    static  result<FIRST> select( FIRST v ) { return type_selector<FIRST>::select(v) ; }

    template < typename T > static  result<T> select( T v ) { return type_selector<REST...>::select(v) ; }
};

#include <string>
#include <complex>
#include <iostream>
#include <cassert>

int main()
{
    using selector = type_selector< char, int, double, std::string, std::complex<double> > ;

    const auto c = selector::select('!').first ;
    const auto i = selector::select(100).first ;
    const auto d = selector::select(99.99).first ;
    const auto str = selector::select( std::string("hello") ).first ;
    const auto cmpx = selector::select( std::complex<double>(1,2) ).first ;

    std::cout << c << ' ' << i << ' ' << d << ' ' << str << ' ' << cmpx << '\n' ;
    assert( selector::select(5).second == typeid(int) ) ;
}
