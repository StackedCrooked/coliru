#include <iostream>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;
int main ()
{
    std::string input = "asd eee rrr HHH 456";
    std::string::iterator strbegin = input.begin();
    int result;
    bool ok = qi::phrase_parse(
            strbegin, input.end(),
            (qi::omit[*(qi::char_ - qi::lit("HHH"))] >> qi::lit("HHH") >> qi::int_),
            qi::space,                  
            result);                               

    std::cout << ok << std::endl;
    std::cout << result << std::endl;
}