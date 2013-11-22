#include <iostream>
#include <type_traits>

template< typename T, typename = void > struct test
     : std::integral_constant<int,1> {} ;

template < typename T >
struct test< T, typename std::enable_if< std::is_integral<T>::value, void >::type >
     :  std::integral_constant<int,2> {} ;

int main()
{
    std::cout << "short: " << test<short>::value << '\n'
              << "double: " << test<double>::value << '\n' ;
}
