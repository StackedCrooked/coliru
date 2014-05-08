// #define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <map>
#include <vector>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

namespace ast
{
    enum op { op_equal, op_inequal, op_like, op_is };

	struct null { };

	typedef boost::variant<null, std::string> value;

	struct condition
	{
		std::string _field;
		op          _op;
		value       _value;
	};

	typedef std::vector<condition> conditions;

	// for debug
	static inline std::ostream& operator<<(std::ostream& os, null) {
		return os << "NULL";
	}
	static inline std::ostream& operator<<(std::ostream& os, op const& o) {
		switch (o) {
		case op_equal:   return os << "=";
		case op_inequal: return os << "<>";
		case op_like:    return os << "LIKE";
		case op_is:      return os << "IS";
		default:         return os << "?";
		}
	}
	static inline std::ostream& operator<<(std::ostream& os, condition const& c) {
		return os << "( [" << c._field << "] " << c._op << " " << c._value << " )";
	}
}

BOOST_FUSION_ADAPT_STRUCT(ast::condition, (std::string, _field)(ast::op, _op)(ast::value, _value))

template <typename It, typename Skipper = qi::space_type>
struct parser : qi::grammar<It, ast::conditions(), Skipper>
{
	parser() : parser::base_type(start)
	{
		using namespace qi;

		// lexemes (no skipper)
		ident = +char_("a-zA-Z._");
		op_token.add
			("=", ast::op_equal)
			("<>", ast::op_inequal)
			("like", ast::op_like)
			("is", ast::op_is);
		op          = no_case [ op_token ];
		nulllit     = no_case [ "NULL" >> attr(ast::null()) ];
		and_        = no_case [ "AND" ];
		stringlit   = "'" >> *~char_("'") >> "'";

		//// other productions
		field       = ident;
		value       = stringlit | nulllit;
		condition   = field >> op >> value;

		whereclause = condition % and_;
		start       = whereclause;

		BOOST_SPIRIT_DEBUG_NODES(
			(ident)(op)(nulllit)(and_)(stringlit) // lexemes
			(field)(value)(condition)(whereclause)(start) // other productions
			)
	}

private:
	qi::rule<It, std::string()> ident, stringlit;
	qi::rule<It, ast::null()>   nulllit;
	qi::rule<It> and_;

	qi::symbols<char, ast::op> op_token;
	qi::rule<It, ast::op()> op;

	qi::rule<It, std::string(),     Skipper> field;
	qi::rule<It, ast::value(),      Skipper> value;
	qi::rule<It, ast::condition(),  Skipper> condition;
	qi::rule<It, ast::conditions(), Skipper> whereclause, start;
};

template <typename C, typename Skipper>
bool doParse(const C& input, const Skipper& skipper)
{
	auto f(std::begin(input)), l(std::end(input));

	parser<decltype(f), Skipper> p;
	ast::conditions data;

	try
	{
		bool ok = qi::phrase_parse(f, l, p, skipper, data);
		if (ok)
		{
			std::cout << "parse success\n";
			std::cout << "No Of Key-Value Pairs=  " << data.size() << "\n";
			for (auto& el : data)
				std::cout << el << "\n";
		}
		else    std::cerr << "parse failed: '" << std::string(f, l) << "'\n";
		return ok;
	}
	catch (const qi::expectation_failure<decltype(f)>& e)
	{
		std::string frag(e.first, e.last);
		std::cerr << e.what() << "'" << frag << "'\n";
	}
	return false;
}

int main()
{
	std::cout << "Pair Test \n";
	const std::string input = "book.author_id = '1234' and book.isbn liKE 'xy99' and book.type = 'abc' and book.lang IS null";
	bool ok = doParse(input, qi::space);
	std::cout << input << "\n";
	return ok ? 0 : 255;
}
