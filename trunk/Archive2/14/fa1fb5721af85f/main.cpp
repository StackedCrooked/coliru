#include <iostream>
#include <functional>
#include <unordered_map>

int foo( double ) { std::cout << "foo was called\n" ; return 0 ; }
long bar( float ) { std::cout << "bar was called\n" ; return 1 ; }

// http://en.cppreference.com/w/cpp/container/unordered_map
// http://en.cppreference.com/w/cpp/utility/functional/function
std::unordered_map< std::string, std::function< long(double) > > hash_table = { { "foo", foo }, { "bar", bar } } ;

int main()
{
    hash_table["bar"]( 23.456 ) ;
}
