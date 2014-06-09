#include <iostream>
#include <string>
#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/home/phoenix.hpp>
#include <boost/variant.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

enum class UnaryOperator
{
    NOT,
	PLUS,
	MINUS,
};

std::ostream& operator<<(std::ostream& os, const UnaryOperator op)
{
	switch (op)
	{
	case UnaryOperator::NOT: os << "!"; break;
	case UnaryOperator::PLUS: os << "+"; break;
	case UnaryOperator::MINUS: os << "-"; break;
	default: assert(false);
	}

	return os;
}

enum class BinaryOperator
{
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	MODULO,
	LEFT_SHIFT,
	RIGHT_SHIFT,
	EQUAL,
	NOT_EQUAL,
	LOWER,
	LOWER_EQUAL,
	GREATER,
	GREATER_EQUAL,
};

std::ostream& operator<<(std::ostream& os, const BinaryOperator op)
{
	switch (op)
	{
	case BinaryOperator::ADD: os << "+"; break;
	case BinaryOperator::SUBTRACT: os << "-"; break;
	case BinaryOperator::MULTIPLY: os << "*"; break;
	case BinaryOperator::DIVIDE: os << "/"; break;
	case BinaryOperator::MODULO: os << "%"; break;
	case BinaryOperator::LEFT_SHIFT: os << "<<"; break;
	case BinaryOperator::RIGHT_SHIFT: os << ">>"; break;
	case BinaryOperator::EQUAL: os << "=="; break;
	case BinaryOperator::NOT_EQUAL: os << "!="; break;
	case BinaryOperator::LOWER: os << "<"; break;
	case BinaryOperator::LOWER_EQUAL: os << "<="; break;
	case BinaryOperator::GREATER: os << ">"; break;
	case BinaryOperator::GREATER_EQUAL: os << ">="; break;
	default: assert(false);
	}

	return os;
}

typedef boost::variant<
	double, 
	int, 
	std::string
> Litteral;

struct Identifier
{
	std::string name;
};
BOOST_FUSION_ADAPT_STRUCT(Identifier, (std::string, name))

struct UnaryOperation;
struct BinaryOperation;
struct FunctionCall;

typedef boost::variant<
	Litteral, 
	Identifier,
	boost::recursive_wrapper<UnaryOperation>,
	boost::recursive_wrapper<BinaryOperation>,
	boost::recursive_wrapper<FunctionCall>
> Expression;

struct UnaryOperation
{
	Expression rhs;
	UnaryOperator op;
};
BOOST_FUSION_ADAPT_STRUCT(UnaryOperation, (UnaryOperator, op)(Expression, rhs))

struct BinaryOperation
{
	Expression rhs, lhs;
	BinaryOperator op;
};
BOOST_FUSION_ADAPT_STRUCT(BinaryOperation, (Expression, rhs)(BinaryOperator, op)(Expression, lhs))

struct FunctionCall
{
	std::string functionName;
	std::vector<Expression> args;
};
BOOST_FUSION_ADAPT_STRUCT(FunctionCall, (std::string, functionName)(std::vector<Expression>, args))

struct Program
{
	std::vector<Expression> statements;
};
BOOST_FUSION_ADAPT_STRUCT(Program, (std::vector<Expression>, statements))

std::ostream& operator<<(std::ostream& os, const Expression& expr)
{
	os << "Expression ";
	FunctionCall call;
	switch (expr.which())
	{
	case 0: os << "(litteral: " << boost::get<Litteral>(expr) << ")"; break;
	case 1: os << "(identifier: " << boost::get<Identifier>(expr).name << ")"; break;
	case 2: os << "(unary op: " << boost::fusion::as_vector(boost::get<UnaryOperation>(expr)) << ")"; break;
	case 3: os << "(binary op: " << boost::fusion::as_vector(boost::get<BinaryOperation>(expr)) << ")"; break;
	case 4: os << "(function call: ";
		call = boost::get<FunctionCall>(expr);
		os << call.functionName << "("; if (call.args.size() > 0) os << call.args.front();
		for (auto it = call.args.begin() + 1; it != call.args.end(); it++) { os << ", " << *it; }
		os << ")"; break;
	default: assert(false);
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const Program& prog)
{
	os << "Program" << std::endl << "{" << std::endl;
	for (const Expression& expr : prog.statements) { std::cout << "\t" << expr << std::endl; }
	os << "}" << std::endl;

	return os;
}

template<typename Iterator, typename Skipper>
struct BoltGrammar : qi::grammar<Iterator, Skipper, Program()>
{
	BoltGrammar() : BoltGrammar::base_type(start)
	{
		start %= expression % ';';
		expression %= identifier | litteral;
		identifier %= qi::lexeme[ascii::char_("a-zA-Z") >> *ascii::char_("0-9a-zA-Z")];
		litteral %= qi::double_ | qi::int_ | quotedString;
		quotedString %= qi::lexeme['"' >> +(ascii::char_ - '"') >> '"'];
	}

	qi::rule<Iterator, Skipper, Program()> start;
	qi::rule<Iterator, Skipper, Expression()> expression;
	qi::rule<Iterator, Skipper, Identifier()> identifier;
	qi::rule<Iterator, Skipper, Litteral()> litteral;
	qi::rule<Iterator, Skipper, std::string> quotedString;
};

typedef std::string::iterator Iterator;
typedef boost::spirit::ascii::space_type Skipper;

int main(int argc, char* argv[])
{
	BoltGrammar<Iterator, Skipper> grammar;

	std::string str;
	while (getline(std::cin, str))
	{
		if (str.empty() || str[0] == 'q' || str[0] == 'Q')
		{
			std::cout << "Exiting..." << std::endl;
			break;
		}

		Program prog;
		Iterator iter = str.begin(), last = str.end();
		bool r = phrase_parse(iter, last, grammar, ascii::space, prog);

		if (r && iter == last)
		{
			std::cout << "Parsing succeeded: " << prog << std::endl;
		}
		else
		{
			std::cout << "Parsing failed, remaining: " << std::string(iter, last) << std::endl;
		}
	}

	std::cin.get();
	return 0;
}