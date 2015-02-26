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
    using namespace boost::phoenix::local_names;

	qi::rule<Iterator, Func()> start;
	
	start = qi::int_ [ 
		qi::_val = px::lambda(_a = qi::_1)[arg1[_a]]
	];

	static char const* inputs[] = { "0", "1", "2", "3", "4", 0 };

	for (char const* const* it = inputs; *it; ++it)
	{
		std::string const input(*it);
		Iterator f(input.begin()), l(input.end());

		Func function;
		bool ok = qi::parse(f, l, start, function);

		if (ok)
			std::cout << "Parse resulted in function() -> character " 
			   << function("Hello") << "; " 
			   << function("World") << "\n";
		else
			std::cout << "Parse failed\n";

		if (f != l)
			std::cout << "Remaining unparsed: '" << std::string(f, l) << "'\n";
	}
}