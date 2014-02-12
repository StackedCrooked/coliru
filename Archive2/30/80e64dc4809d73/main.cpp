#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

// split a string into comma delimited segments
// http://www.mochima.com/tutorials/vectors.html
std::vector<std::string> split_on_commas( const char* cstr )
{
    std::vector<std::string> segments ;

    // http://latedev.wordpress.com/2011/11/16/c-stringstreams/
    std::istringstream stm( cstr ) ;

    std::string token ;

    // http://www.cplusplus.com/reference/string/string/getline/
    while( std::getline( stm, token, ',' ) ) segments.push_back(token) ;

    return segments ;
}

// given a string of the form abcd=nnn.nn, extract then into a (string,double) pair
// http://www.cplusplus.com/reference/utility/pair/
std::pair< std::string, double > make_mame_value_pair( const std::string& token )
{
    std::istringstream stm( token ) ;

    std::string name ;
    double value ;

    std::getline( stm, name, '=' ) ;
    stm >> value ;

    // http://www.stroustrup.com/C++11FAQ.html#uniform-init
    return { name, value } ;
}

int main()
{
    // place a chunk of the streaming data into a null-terminated string
    char cstr[] = "V=13.7,FV=13.7,V2=00.0,A=00.1,FA=00.1,AH=0.18,%=100,W=0.82,DSC=1.87,DSE=1.98," ;
    std::cout << cstr << '\n' ;

    // http://www.stroustrup.com/C++11FAQ.html#for
    for( const auto& tok : split_on_commas(cstr) )
    {
        auto pair = make_mame_value_pair(tok) ;
        std::cout << "name: '" << pair.first << "'  value: " << pair.second << '\n' ;
    }
}
