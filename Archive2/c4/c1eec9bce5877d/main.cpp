#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

int main()
{
    std::cout<<"Converting decimal to binary\n\n" ;
    std::srand( std::time(nullptr) ) ;

    const std::size_t n = 1 + std::rand()%5 ;

    for( std::size_t i = 0 ; i < n ; ++i )
    {
        int number = std::rand()%10 ;
        std::cout << number << ' ' ;

        std::vector<int> binary ;

        while( number > 0 )
        {
            binary.push_back( number%2 ) ;
            number /= 2 ;
        }

        binary.resize(4) ;
        std::reverse( binary.begin(), binary.end() ) ; // reverse the digits

        for( int b : binary ) std::cout << b ;
        std::cout << '\n' ;
    }
}
