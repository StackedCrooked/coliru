#include <iostream>
#include <string>
#include <stdexcept>

enum class colour { WHITE, GREY, BLACK } ;

std::string to_string( colour clr )
{
    switch(clr)
    {
        case colour::WHITE: return "colour::WHITE" ;
        case colour::GREY: return "colour::GREY" ;
        case colour::BLACK: return "colour::BLACK" ;
    }

    throw std::domain_error( "uninitialized colour" ) ;
}

std::ostream& operator<< ( std::ostream& stm, colour clr )
{ return stm << to_string(clr) ; }

int main()
{
     const auto clr_cloud = colour::GREY ;
     std::cout << clr_cloud << '\n' ;
}
