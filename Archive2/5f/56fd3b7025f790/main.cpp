#include <boost/spirit/include/qi.hpp>
#include <sstream>

namespace qi = boost::spirit::qi;

int main()
{
    typedef boost::spirit::istream_iterator Iterator;

    std::istringstream iss("[[This is some single-spaced text]]");
    qi::rule<Iterator, std::string()> entry = "[[" >> qi::lexeme [ +(qi::char_ - "]]") ] >> "]]";
    
    // this is key:
    iss >> std::noskipws; // or:
    iss.unsetf(std::ios::skipws);

    Iterator f(iss), l;
    std::string parsed;
    if (qi::parse(f, l, entry >> -qi::eol, parsed))
    {
        std::cout << "Parsed: '" << parsed << "'\n";
    } else
        std::cout << "Failed";

    if (f!=l)
        std::cout << "Remaining: '" << std::string(f,l) << "'\n";
}
