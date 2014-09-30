#include <regex>
#include <string>
#include <iostream>

int main()
{
    const std::string s = "Hello, my name is Ben. Please visit "
                          "my website at http://forta.com/.";

    const std::regex e( "Ben", std::regex_constants::basic );
    std::smatch m;

    /*while*/if( std::regex_search( s, m, e ) )  
                 std::cout << "Hello " << m[ /*1*/ 0 ] << '\n' ;
}
