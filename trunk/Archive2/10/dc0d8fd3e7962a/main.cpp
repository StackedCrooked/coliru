#include <iostream>
#include <map>
#include <string>

namespace
{
    std::map< std::string, int > ints ;
    std::map< std::string, std::string > strings ;

    void create_variable( std::string name, int value )
    { ints[name] = value ; }

    void create_variable( std::string name, std::string value )
    { strings[name] = value ; }
}

int main()
{
    create_variable( "count", 5 ) ;
    create_variable( "total", 0 ) ;
    create_variable( "name", "anonymous" ) ;
    create_variable( "file", "my_data.txt" ) ;
    create_variable( "message", "hello" ) ;

    int& cnt = ints["count"] ;
    cnt += 8 ;

    std::string& msg = strings["message"] ;
    msg += " world" ;

    for( auto& p : ints ) std::cout << p.first << " == " << p.second << '\n' ;
    for( auto& p : strings ) std::cout << p.first << " == " << p.second << '\n' ;
}
