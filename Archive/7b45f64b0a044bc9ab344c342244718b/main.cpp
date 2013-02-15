#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted.hpp>
#include <tuple>

namespace qi = boost::spirit::qi;

main( int argc, char* argv[] )
{
    qi::rule<std::string::iterator,std::tuple<int,int>()> parser;

    parser = 
        (qi::int_ >> '(' >> qi::int_ >> ')')
        ;
}