#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;

int main()
{
    std::istringstream iss("1 2 3 4 5; 6 7 8 9;");
    iss.unsetf(std::ios::skipws);

    std::vector<int> i;
    std::vector<double> d;

    if (iss >> qi::phrase_match(qi::auto_ >> ";" >> qi::auto_, qi::space, i, d))
    {
        for (auto e:i) std::cout << "int: " << e << "\n";
        for (auto e:d) std::cout << "double: " << e << "\n";
    }
}
