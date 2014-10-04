#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    qi::rule<std::string::const_iterator, char()> a  = qi::char_("a");
    qi::rule<std::string::const_iterator, char()> b  = qi::char_("b");
    qi::rule<std::string::const_iterator>         bc = qi::lit("bc");
    qi::rule<std::string::const_iterator, std::string()> expr;
    BOOST_SPIRIT_DEBUG_NODES((a)(b)(bc)(expr))
    
    expr = +a >> -(b >> +a);

    std::string res;

    std::string const str = "abc";
    std::string::const_iterator f(str.begin()), l(str.end());

    bool r = qi::parse(f, l, expr >> bc, res);

    if (r)
        std::cout << "Success: '" << res << "'\n";
    else
        std::cout << "Failed\n";

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "\n";
}
