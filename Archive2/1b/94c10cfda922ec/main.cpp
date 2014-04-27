#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    std::string const s = "[ 0.562 , 1.4e-2 ]"; // example input
    std::string::const_iterator f(s.begin()), l(s.end());

    float f1 = 0.0f, f2 = 0.0f;

    if (qi::phrase_parse(f, l,
                '[' >> qi::double_ >> ',' >> qi::double_ >> ']',
                qi::space, 
                f1, f2))
    {
        std::cout << "Parsed: " << f1 << " and " << f2 << "\n"; // default formatting...
    } else
    {
        std::cout << "Error while parsing" << std::endl;
    }

    if (f!=l)
        std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
}
