#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <sstream>

namespace qi = boost::spirit::qi;

int main()
{
    std::istringstream buffer("NbProducts = 1234;");

    int NbProducts;
    if (buffer >> qi::phrase_match(
            qi::lit("NbProducts") >> "=" >> qi::int_ >> ";", 
            qi::space, NbProducts))
    {
        std::cout << "Matched: " << NbProducts << "\n";
    } else
    {
        std::cout << "Not matched\n";
    }
}
