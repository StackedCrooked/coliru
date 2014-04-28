#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <sstream>

namespace qi = boost::spirit::qi;

int main()
{
    std::istringstream ss("[ 0.562 , 1.4e-2 ]"); // example input
    ss.unsetf(std::ios::skipws); // we might **want** to handle whitespace in our grammar, not needed now

    float f1 = 0.0f, f2 = 0.0f;

    if (ss >> qi::phrase_match('[' >> qi::double_ >> ',' >> qi::double_ >> ']', qi::space, f1, f2))
    {
        std::cout << "Parsed: " << f1 << " and " << f2 << "\n"; // default formatting...
    } else
    {
        std::cout << "Error while parsing" << std::endl;
    }
}
