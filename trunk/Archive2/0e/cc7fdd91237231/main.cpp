#include <string>
#include <iostream>
#include <boost/spirit/include/qi.hpp>

int main()
{
    using namespace boost::spirit::qi ;

    const std::string s = "11:12:13 14+15*16/17 --18-+:19" ;

    std::vector<int> numbers ;

    parse( s.begin(), s.end(), int_ % +char_(": +*/-"), numbers ) ;
    for( int v : numbers ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
