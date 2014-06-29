#include <iostream>
#include <string>
#include <set>
#include <type_traits>

template < typename T >
typename std::enable_if< std::is_pointer<T>::value >::type
my_print( const std::set<T>& set )
{
    std::cout << "size: " << set.size() << ", contains pointers [ " ;
	for( auto i = set.begin() ; i != set.end(); ++i )
	    if( *i ) std::cout << **i << ' ' ;
        else std::cout << "null " ;
	std::cout << "]\n";
}

template < typename T >
typename std::enable_if< !std::is_pointer<T>::value >::type
my_print( const std::set<T>& set )
{
	std::cout << "size: " << set.size() << ", contains values [ " ;
	for( auto i = set.begin() ; i != set.end(); ++i ) std::cout << *i << ' ' ;
	std::cout << "]\n";
}

int main()
{
    const std::set<std::string> set_of_values { "one", "two", "three" } ;
    my_print(set_of_values) ;

    std::set< const std::string* > set_of_pointers ;
    for( const auto& str : set_of_values ) set_of_pointers.insert( std::addressof(str) ) ;
    my_print(set_of_pointers) ;
}
