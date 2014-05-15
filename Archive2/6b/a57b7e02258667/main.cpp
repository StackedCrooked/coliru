#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace qi    = boost::spirit::qi;
namespace lex   = boost::spirit::lex;

#define USE_MYINT
#define USE_LEXER
// #define USE_AUTO_SELECT

// my grammar replacing int_
template<typename Iterator, typename Skipper=qi::space_type>
struct my_int : qi::grammar<Iterator, int(), Skipper>
{
    qi::rule<Iterator, int(), Skipper> start;

	template<typename TokenDef>
	my_int(TokenDef &tok): my_int::base_type(start)
		{
#ifdef USE_AUTO_SELECT
		start %= lex_int(tok);
#elif defined(USE_LEXER)
		start %= tok.integer_;
#else
		start %= qi::int_;
#endif
		BOOST_SPIRIT_DEBUG_NODE(start);
	}

	// overload for lexer
	template<typename TokenDef>
	decltype(start) lex_int(TokenDef &tok)
	{
		return tok.integer_;
	}

	// overload for no lexer
	// template<typename TokenDef>
	decltype(start) lex_int(qi::unused_type)
	{
		return qi::int_;
	}
};

// grammar

template<typename Iterator, typename Skipper=qi::space_type>
struct my_list : qi::grammar<Iterator, std::vector<int>(), Skipper>
{
	template<typename TokenDef>
	my_list(TokenDef &tok): my_list::base_type(start)
	{
#ifdef USE_MYINT
		// XXX leaks
		expr %= *new my_int<Iterator, Skipper>(tok);
#elif defined(USE_LEXER)
		expr %= tok.integer_;
#else
		expr  %= qi::int_;
#endif
		start %= expr % ',';

		BOOST_SPIRIT_DEBUG_NODE(start);
		BOOST_SPIRIT_DEBUG_NODE(expr);
	}
	qi::rule<Iterator, int(), Skipper> expr;
	qi::rule<Iterator, std::vector<int>(), Skipper> start;
};

template <typename Lexer>
struct Tokens: lex::lexer<Lexer>
{
	public:
		Tokens()
	{
		using lex::_pass;
		using lex::_tokenid;
		using lex::_start;

		whitespace_ = "\\s+";
		integer_	= "\\d+";
		char_		= ".";

		this->self  = whitespace_ [_pass = lex::pass_flags::pass_ignore]
					| integer_
					| char_ 	  [_tokenid = *_start]
					;
    }
  	lex::token_def<int>	integer_;
  	lex::token_def<int> char_;
  	lex::token_def<> whitespace_;
};

// send vec of tokens to ostream
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	for (auto& e : v)
	{
		os << std::hex << e;
		if (isprint(e)) { os << "[" << static_cast<char>(e) << "] "; }
		os << ", ";
	}
	return os;
}

int main()
{
	for (auto& input : std::list<std::string> {
		"1, 2;",
		"3, 4, 5;"
	}) {
		std::cout << "input: " << input << std::endl;
		std::vector<int> result;

#ifndef USE_LEXER
		// just use qi parsers
		auto first(std::begin(input)), last(std::end(input));
		my_list<decltype(first)> p(qi::unused);
		bool ok = qi::phrase_parse(first, last, p > ';', qi::space, result);
		std::string unparsed(first, last);
#else
		// use a spirit lexer
		using token_type = lex::lexertl::token<char const *, boost::mpl::vector<int, std::string>>;
		using lexer_type = lex::lexertl::actor_lexer<token_type>;

		Tokens<lexer_type> my_lexer;
		const char *f = input.c_str();
		const char *l = &f[input.size()];
		auto first = my_lexer.begin(f, l);
		auto last  = my_lexer.end();
		my_list<decltype(first), qi::unused_type> p(my_lexer);
		bool ok = qi::parse(first, last, p > ';', result);
		std::vector<token_type> unparsed(first, last);
#endif

		if (!ok)
			std::cout << "invalid input\n";
		else
			std::cout << "result: " << result << std::endl;

		if (first != last)
			std::cout << "unparsed: '" << unparsed << std::endl; }

		return 0;
}