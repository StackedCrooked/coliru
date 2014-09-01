#include <iostream>
#include <string>
#include <vector>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;


int main( int, char *[] )
{
    const std::string test( "1 2" );
    typedef std::string::const_iterator iterator;

    auto desired = []( int a, int b )
    {
        std::cout << a << ", " << b << std::endl;
    };

    /*auto working = []( boost::fusion::vector2<int,int> )
    {
    };*/

    iterator i = test.begin( );
    qi::phrase_parse( i, test.end( ),
                     (
                      qi::int_ >>
                       qi::int_
                      )
//                     [ working ]
                   [ ph::bind( desired, qi::_1, qi::_2 ) ]
                     , qi::ascii::space );

    return test.end( ) - i;
}