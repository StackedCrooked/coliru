#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <iostream>
#include <sstream>

namespace qi = boost::spirit::qi;

int main()
{
    std::istringstream input("some text that i'd like to ignore 42 \tthe rest of line");

    int number;

    if (input >> std::noskipws >> qi::phrase_match(
             "some text that i'd like to ignore" 
          >> qi::int_ 
          >> "the rest of line", qi::space, number))
    {
        std::cout << "Successfully parsed (" << number << ")\n";
    }

}
