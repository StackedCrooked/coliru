#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>

struct order
{
    enum class status : unsigned int { NEW_ORDER = 0, CONFIRMED = 1, SHIPPED = 2, FILLED = 3 };

    static std::string to_string( status s ) ;

};

inline std::ostream& operator<< ( std::ostream& stm, order::status s )
{ return stm << order::to_string(s) ; }

// ------------- cpp file -----------------

namespace
{
    constexpr const char* const order_status_string[] =
    { "NEW_ORDER", "CONFIRMED", "SHIPPED", "FILLED" } ;

    inline bool initialized( order::status s ) { return s <= order::status::FILLED ; }
}

std::string order::to_string( order::status s )
{
    assert( "order::status has been initialized" && initialized(s) ) ;
    static const std::string prefix = "order::" ;
    if( initialized(s) ) return prefix + order_status_string[ std::size_t(s) ] ;
    throw std::domain_error( "uninitialized order::status" ) ;
}

int main()
{
    try
    {
        std::cout << order::status::CONFIRMED << std::endl ;
        order::status uninitialized ;
        std::cout << uninitialized << '\n' ;
    }
    catch( const std::exception& e )
    {
        std::cerr << "*** exception: " << e.what() << '\n' ;
    }
}
