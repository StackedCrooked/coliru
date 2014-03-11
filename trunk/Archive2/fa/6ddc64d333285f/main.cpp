#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

std::vector<char> spin( std::string letters, std::size_t n = 10 )
{
    std::random_shuffle( letters.begin(), letters.end() ) ;
    if( n  > letters.size() ) n = letters.size() ;
    return std::vector<char>( letters.begin(), letters.begin() + n ) ;
}


int main()
{
    std::srand( std::time(nullptr) ) ;
    
    for( int i = 0 ; i < 4 ; ++i )
    {
        for( char c : spin( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ) ) std::cout << c ;
        std::cout << ' ' ;
    
        for( char c : spin( "AAABBCDDEEEFFGGHIIIIJKLLMMMNNNNPQRSSSTTTTUVUWXYZ" ) )
            std::cout << c ;
        std::cout << '\n' ;
    } 
}
