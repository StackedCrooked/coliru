#include <boost/spirit/include/qi.hpp>
#include <fstream>

namespace qi   = boost::spirit::qi;

int main()
{
    std::ifstream ifs("main.cpp");
    ifs >> std::noskipws;

    boost::spirit::istream_iterator f(ifs), l;

    std::string parsed;
    bool ok = qi::parse(
            f, l, 
               qi::omit [ *(qi::char_ - (qi::eol >> "int main")) >> qi::eol ]
            >> +(qi::char_ - qi::eol),
            parsed
        );

    if (ok)
        std::cout << "Found: '" << parsed << "'\n";
    else
        std::cout << "Fail at: '" << std::string(f,l) << "'\n";
}
