#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

namespace boost {
    // hack for debug printing
	template <typename T>
	static inline std::ostream& operator<< (std::ostream& os, std::vector<T> const& v) {
		std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, ";"));
		return os;
} }

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phx   = boost::phoenix;

typedef std::vector<double> number_array;
typedef std::vector<std::string> string_array;

typedef boost::variant<number_array, string_array> node;

template<typename Iterator>
struct parser : qi::grammar<Iterator, node(), ascii::space_type> {

	parser()
		: parser::base_type(expr_)
	{
		number_array_ = "n[" >> -(qi::double_ % ',') >> ']';
		string_array_ = "s[" >> -(quoted_string % ',') >> ']';

		quoted_string %= "'" > qi::lexeme[*(qi::char_ - "'")] > "'";

		expr_ = number_array_ | string_array_;
	}

	qi::rule<Iterator, number_array(), ascii::space_type> number_array_;
	qi::rule<Iterator, string_array(), ascii::space_type> string_array_;
	qi::rule<Iterator, std::string(),  ascii::space_type> quoted_string;
	qi::rule<Iterator, node(),         ascii::space_type> expr_;
}; 

int main()
{
	parser<std::string::const_iterator> p;

	for (std::string const s : {
		"n[1,2,3,4,5,6,7,-9]",
		"s['aap','noot','mies']"
	})
	{
		auto f(s.begin()), l(s.end());
		node data;
		bool ok = qi::phrase_parse(f, l, p, ascii::space, data);
		if (ok)
			std::cout << "Parsed: '" << s << "' into " << data << "\n";
		else
			std::cout << "Error parsing '" << s << "'\n";

		if (f != l)
			std::cout << "Remaining input: '" << std::string(f, l) << "'\n";
	}
}
