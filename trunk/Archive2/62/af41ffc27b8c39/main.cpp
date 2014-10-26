#include <iostream>
#include <boost/spirit/home/qi.hpp>
#include <vector>
#include <string>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

struct escapedDoubleQuote_ : qi::symbols<char, std::string >
{
    escapedDoubleQuote_()
    {
        add("\"\"", "\\\"");
    }
} escapedDoubleQuote;

template<typename Iterator>
struct MyGrammar : qi::grammar<Iterator, std::string()>
{
    MyGrammar() : MyGrammar::base_type(start)
    {
        subField     = +(~qi::char_("\""));
        escapedField = subField >> -(escapedDoubleQuote >> escapedField);
        start        = escapedField;
    }

    qi::rule<Iterator, std::vector<char>()> subField, escapedField;
    qi::rule<Iterator, std::string()> start;
};

int main()
{
    typedef std::string::const_iterator iterator_type;
    typedef MyGrammar<iterator_type> parser_type;
    parser_type parser;

    std::string input = "123\"\"456\"\"789";
    std::string output;
    iterator_type it = input.begin();
    bool parsed = parse(
            it,
            input.cend(),
            parser,
            output
    );

    if(parsed && it == input.end())
    {
        std::cout << output << std::endl;
        // expected: 123\"456\"789
        // actual  : \"789
    }

    return 0;
}
