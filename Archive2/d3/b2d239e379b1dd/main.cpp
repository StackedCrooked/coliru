#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <string>

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace ascii = boost::spirit::ascii;
namespace phx = boost::phoenix;
using boost::phoenix::ref;


template <typename Iterator>
struct x_grammar : public qi::grammar<Iterator, ascii::space_type, qi::locals<qi::rule<Iterator, ascii::space_type>*> >
{
public:
    x_grammar() : x_grammar::base_type(start_rule, "x_grammar")
	{
		using namespace qi;

		int_rule = int_   [std::cout << phx::val("int ") << _1 << ".\n"];
		dbl_rule = double_[std::cout << phx::val("double ") << _1 << ".\n"];
		subrules.add
			("I", &int_rule)
			("D", &dbl_rule);

		start_rule = subrules[_a = _1] >> lazy(*_a);
	}
private:
	typedef qi::rule<Iterator, ascii::space_type> subrule;

	qi::symbols<char, subrule*> subrules;
	qi::rule<Iterator, ascii::space_type, qi::locals<subrule*> > start_rule;
	qi::rule<Iterator, ascii::space_type> int_rule, dbl_rule;
};

int main()
{
	typedef std::string::const_iterator iter;
	std::string storage("I 5");
	iter it_begin(storage.begin());
	iter it_end(storage.end());
	using boost::spirit::ascii::space;
	x_grammar<iter> g;
	try {
		bool r = qi::phrase_parse(it_begin, it_end, g, space);
		if (r) {
			std::cout << "Pass!\n";
		}
		else {
			std::cout << "Fail!\n";
		}
	}
	catch (const qi::expectation_failure<iter>&) {
		std::cout << "Fail!\n";
	}
	return 0;
}