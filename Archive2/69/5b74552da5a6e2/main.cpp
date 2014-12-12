#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main() {
    std::string const input(".name \"this is my name\"");

    auto f(input.begin()), l(input.end());


    std::string parsed_name;
    if (qi::phrase_parse(f,l,
                qi::lexeme[".name"] >> qi::lexeme['"' >> *~qi::char_('"') >> '"'],
                qi::space,
                parsed_name))
    {
        std::cout << "Parsed: '" << parsed_name << "'\n";
    }
    else
    {
        std::cout << "Parsed failed\n";
    }

    if (f!=l)
        std::cout << "Remaining unparsed input: '" << std::string(f,l) << "'\n";
}
