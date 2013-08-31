#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
namespace qi = boost::spirit::qi;

static const qi::rule<std::string::const_iterator, std::string(const char*)> start 
     = *(qi::char_ - qi::char_(qi::_r1));

int main()
{
    const std::string test("bla%47blo/bli");
    return qi::parse(begin(test), end(test), start(+"/") [ std::cout << qi::_1 ])
        ? 0 : 255;
}
