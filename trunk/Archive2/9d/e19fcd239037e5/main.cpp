#include <random>
#include <vector>
#include <algorithm>
#include <iostream>

int main()
{
    std::size_t p = 10;
	
	std::normal_distribution<> dis;
	std::mt19937 mt;
	std::vector<double> vec;
	std::generate_n( std::back_inserter(vec), p, [&]{ return dis(mt); } );

	for( auto d : vec )
		std::cout << d << '\n';
}