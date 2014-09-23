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
    using namespace boost::phoenix::arg_names;

	qi::rule<Iterator, Func()> start;
	
	start = qi::int_ [ 
		qi::_val = px::bind(px::lambda[arg1[arg2]], px::lambda[arg1], qi::_1)
	];

	for (std::string const input : { "0", "1", "2", "3", "4" })
	{
		Iterator f(input.begin()), l(input.end());

		Func f;
		bool ok = qi::parse(f, l, start, f);

		if (ok)
			std::cout << "Parse resulted in f() -> character " 
			   << f("Hello") << "; " 
			   << f("World") << "\n";
		else
			std::cout << "Parse failed\n";

		if (f != l)
			std::cout << "Remaining unparsed: '" << std::string(f, l) << "'\n";
	}
}
