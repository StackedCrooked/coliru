#include <boost/variant.hpp>
#include <boost/spirit/include/karma.hpp>

namespace karma = boost::spirit::karma;
typedef boost::variant<int, std::string> Parameter;
typedef std::vector<Parameter> Parameters;

typedef boost::spirit::ostream_iterator It;

void test(boost::variant<Parameters, Parameter> const& v)
{
    using namespace karma;
    const static rule<It, std::string()> quoted
        = '"' << *('\\' << char_('"') | char_) << '"'
        ;
    const static rule<It, Parameter()>   param
        = int_ | quoted
        ;
    const static rule<It, boost::variant<Parameters, Parameter>()> rule
        = param | param % ", "
        ;

    std::cout << karma::format(rule, v) << '\n';
}

int main()
{
    test( 1);
    test( "foo");
    test( "escape: \"foo\"");
    test(Parameters { 1, 2, 3, "escape: \"foo\"" });
}