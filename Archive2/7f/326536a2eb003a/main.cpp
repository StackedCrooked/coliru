
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>

int main()
{
    std::string some_string = "-0.003  79350   -0.267  147";
	std::istringstream s(some_string);
	const size_t n = std::distance( std::istream_iterator<std::string>( s ) , std::istream_iterator<std::string>() );
    
	std::vector<std::string> vec( n );
	vec.push_back( some_string );
	auto itr = vec.begin();
	while( itr != vec.end() )
	{
		std::cout << *( itr++ );
	}
	
	return EXIT_SUCCESS;
}
	
	