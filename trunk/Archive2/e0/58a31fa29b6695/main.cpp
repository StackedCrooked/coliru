#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <iostream>
#include <sstream>

namespace qi = boost::spirit::qi;

int main()
{
    std::istringstream input("abc something 123 beautiful");

    std::string abc;
    int number;

    if (input >> abc >> qi::match("something") >> number >> qi::match("beautiful"))
        std::cout << "Successfully parsed ('" << abc << "', " << number << ")\n";
}
