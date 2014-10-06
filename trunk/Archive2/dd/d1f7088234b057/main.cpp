#include <iostream>
#include <string>

int main()
{
    std::string line ;
    while( std::getline( std::cin, line ) ) 
        std::cout << "[in reverse]: " << std::string( line.rbegin(), line.rend() ) << '\n' ;
}
