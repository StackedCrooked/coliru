#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/function.hpp>

namespace qi = boost::spirit::qi;
namespace px = boost::phoenix;

typedef boost::function<char(char const*)> Func;

int main()
{
    typedef std::string::const_iterator Iterator;
    using boost::phoenix::arg_names::arg1;

	qi::rule<Iterator, Func()> start;
	
  	start = qi::int_ [qi::_val = px::lambda[*arg1]];

    std::string const input = "42";
    Iterator f(input.begin()), l(input.end());

	Func output;
    bool ok = qi::parse(f, l, start, output);

	if (ok)
		std::cout << "Parse resulted in f() -> character '" << output("Hello") << "'; '" << output("World") << "'\n"
		;
    else
        std::cout << "Parse failed\n";

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
