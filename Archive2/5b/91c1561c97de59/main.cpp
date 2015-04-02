
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>

int main()
{
	std::istringstream s( "-0.003  79350   -0.267  147" );
	size_t n = std::distance( std::istream_iterator<std::string>( s ) , std::istream_iterator<std::string>() );
	std::vector<std::string> vec(n);
	std::cout << vec.size() << std::endl;
	
	return EXIT_SUCCESS;
}
	
	