#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    using boost::phoenix::ref;
    using namespace qi;

    const std::string input("1234 X abcd efgh");
    auto first(begin(input)), last(end(input));

    unsigned num;
    std::string parsed_str;

    bool ok = qi::phrase_parse(first, last,
            uint_ >> 'X' >> lexeme[+graph],
            blank, 
            num, parsed_str);

    if (ok)
    {
        std::cout << "num=" << num << ", parsed_str='" << parsed_str << "'\n";
    } else
    {
        std::cout << "parse failed\n";
    }

    if (first!=last)
        std::cout << "Trailing unparsed characters: '" << std::string(first, last) << "'\n";
}
