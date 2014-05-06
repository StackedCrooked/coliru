#include <iostream>
#include <type_traits>

// http://en.cppreference.com/w/cpp/language/sfinae
// http://en.cppreference.com/w/cpp/types/enable_if
// http://en.cppreference.com/w/cpp/types/is_same
template < typename A, typename B >
typename std::enable_if< std::is_same<A,B>::value, void >::type
func( A, B ) { std::cout << "both parameters are of the same type\n" ; }

template < typename A, typename B >
typename std::enable_if< !std::is_same<A,B>::value, void >::type
func( A, B ) { std::cout << "parameters are of two diferent types\n" ; }

int main()
{
    func( 12, 16 ) ; // both parameters are of the same type
    
    func( 12, 16.0 ) ; // parameters are of two diferent types
}
