#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
// #include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;
typedef std::string::const_iterator It;

namespace ast
{
    struct Woot
    {
        std::string data;
        double something;
        int awful;
    };
}

BOOST_FUSION_ADAPT_STRUCT(ast::Woot, (int, awful)(double, something)(std::string, data))

int main()
{
    std::string const input ("1 2 3 4");
    It f(begin(input)), l(end(input));

    ast::Woot parsed;

    bool ok = qi::phrase_parse(f, l, qi::int_ >> qi::double_ >> qi::lexeme[*qi::char_], qi::space, parsed);
    if (ok)   
    {
        std::cout << "parse success\n";
        std::cout << "data: " << karma::format_delimited(karma::auto_, '\n', parsed) << "\n";
    }
    else std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

    if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
    return ok? 0 : 255;
}
