#include <iostream>
#include <vector>

int main()

{
    std::vector<int> test { 1, 2, 3, 0, 4, 0, 0, 5 };

	for( auto it = test.cbegin(); it != test.cend() && *it != 0 ; ++it )
		std::cout << *it << ' ';
	std::cout << '\n' ;

	for( std::size_t i = 0 ; i != test.size() && test[i] != 0 ; ++i )
		std::cout << test[i] << ' ';
	std::cout << '\n' ;

	for( int v : test )
    {
        if( v == 0 ) break ;
        std::cout << v << ' ' ;
    }
	std::cout << '\n' ;
}
