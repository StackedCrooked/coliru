#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> split_ws( std::string str )
{
    std::vector<std::string> result ;

    std::istringstream stm(str) ; // http://www.artima.com/cppsource/streamstrings3.html
    std::string token ;
    while( stm >> token ) result.push_back(token) ;

    return result ;
}

int main()
{
    for( std::string s : split_ws( "I like to code" ) ) std::cout << s << '\n' ;
}
