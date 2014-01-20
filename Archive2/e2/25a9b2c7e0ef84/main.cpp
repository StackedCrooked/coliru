#include <iostream>
#include <map>
#include <string>
#include <cstdlib> // std::strtol

// we wouldn't have std::stoi, so we will write a function
int string_to_int( std::string str ) // error checks elided
{ return std::strtol( str.c_str(), 0, 10 ) ; }

struct profile
{
    // the setter_type is now a pointer to member function
    typedef void (profile::*setter_type)( std::string ) ;

    void set( std::string name, std::string value )
    {
        std::map< std::string, setter_type >::const_iterator iter = setters.find(name) ;
        if( iter != setters.end() )
        {
            setter_type pfn = iter->second ; // get the pointer to member function
            ( this->*pfn )(value) ; // and call it with value as the argument
        }
    }

    // a constructor to initialize members
    profile() : id("none"), height(0), width(0) {}

    std::string id ;
    int height ;
    int width ;
    // etc.

    // member functions to set the values
    void set_id( std::string str_id ) { id = str_id ; }
    void set_height( std::string str_height ) { height = string_to_int(str_height) ; }
    void set_width( std::string str_width ) { width = string_to_int(str_width) ; }
    // etc.

    static std::map< std::string, setter_type > setters ;
    static bool init_helper() ;
    static const bool init ;
};

std::map< std::string, profile::setter_type > profile::setters ;

// helper function to populate the map
bool profile::init_helper()
{
    setters["id"] = &profile::set_id ;
    setters["height"] = &profile::set_height ;
    setters["width"] = &profile::set_width ;
    // etc.
    return true ;
}

const bool profile::init = init_helper() ; // populates map by calling init_helper()

std::ostream& operator<< ( std::ostream& stm, const profile& p )
{
    return stm << "profile { id:" << p.id << ", height:" << p.height
                << ", width:" << p.width << " }" ;
}

int main()
{
    profile p ;
    std::cout << p << '\n' ;

    p.set( "id", "local" ) ;
    std::cout << p << '\n' ;

    p.set( "height", "3456" ) ;
    std::cout << p << '\n' ;

    p.set( "width", "999" ) ;
    std::cout << p << '\n' ;
}
