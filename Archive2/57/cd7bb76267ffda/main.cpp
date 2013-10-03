#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <tuple>

template< typename t, std::size_t n, typename = void >
struct function_argument_type;

template< typename r, typename c, typename ... a, std::size_t n >
struct function_argument_type< r (c::*)( a ... ), n >
    { typedef typename std::tuple_element< n, std::tuple< a ... > >::type type; };

template< typename r, typename c, typename ... a, std::size_t n >
struct function_argument_type< r (c::*)( a ... ) const, n >
    : function_argument_type< r (c::*)( a ... ), n > {};

template< typename ftor, std::size_t n >
struct function_argument_type< ftor, n,
    typename std::conditional< false, decltype( & ftor::operator () ), void >::type >
    : function_argument_type< decltype( & ftor::operator () ), n > {};


int main() {
    auto x = []( int, long, bool ){};
    std::cout << typeid( function_argument_type< decltype(x), 0 >::type ).name() << '\n';
    std::cout << typeid( function_argument_type< decltype(x), 1 >::type ).name() << '\n';
	std::cout << typeid( function_argument_type< decltype(x), 2 >::type ).name() << '\n';
}
