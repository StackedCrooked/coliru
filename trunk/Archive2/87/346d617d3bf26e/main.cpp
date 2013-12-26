#include <iostream>
#include <string>
#include <type_traits>

template< typename, typename = void >
struct has_hash : std::false_type {};

template< typename T >
struct has_hash< T, decltype( std::hash< T >()( std::declval< T >() ), void() ) > : std::true_type {};

int main()
{
    std::cout << has_hash< std::string >::value << std::endl;
    std::cout << has_hash< std::ostream >::value << std::endl;
}
