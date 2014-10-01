#include <string>
#include <regex>
#include <iostream>

bool ABCheck( const std::string &str );

int main()
{
    std::cout << "lane borrowed: " << ABCheck( "lane borrowed" ) << std::endl;
    std::cout << "after badly: " << ABCheck( "after badly" ) << std::endl;
    std::cout << "Laura sobs: " << ABCheck( "Laura sobs" ) << std::endl;

    return 0;
}

bool ABCheck( const std::string &str )
{
    std::regex e( "a.\\{3\\}b", std::regex_constants::basic );

    if ( std::regex_search( str, e ) ) {
        return true;
    } else {
        return false;
    }
}