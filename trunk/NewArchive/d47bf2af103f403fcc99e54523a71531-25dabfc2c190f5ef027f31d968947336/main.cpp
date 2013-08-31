#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;

static const qi::rule<std::string::const_iterator, std::string(const char*)> start 
     = *(qi::char_ - qi::char_(qi::_r1));

int main()
{
    std::string const input("bla%47blo/bli");
    std::string parsed;
    if (qi::parse(begin(input), end(input), start(+"/"), parsed))
        std::cout << parsed;
}
