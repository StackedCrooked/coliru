#include <iostream>
#include <map>
#include <string>
#include <functional>

struct profile
{
    void set( std::string name, std::string value )
    {
        auto iter = setters.find(name) ;
        if( iter != setters.end() ) iter->second( this, value ) ;
    }

    std::string id = "none" ;
    int height = 0 ;
    // etc.

    using setter_type = std::function< void( profile*,  std::string ) > ;
    static const std::map< std::string, setter_type > setters ;
};

const std::map< std::string, profile::setter_type > profile::setters
{
    { "id", []( profile* This, std::string value ) { This->id = value ; } },
    { "height", []( profile* This, std::string value ) { This->height = std::stoi(value) ; } }
    // etc.
};

int main()
{
    profile p ;
    std::cout << "id: " << p.id << "   height: " << p.height << '\n' ;
    
    p.set( "id", "this is a local profile" ) ;
    std::cout << "id: " << p.id << "   height: " << p.height << '\n' ;

    p.set( "height", "3456789" ) ;
    std::cout << "id: " << p.id << "   height: " << p.height << '\n' ;
}
