//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;
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
        case UnaryOperator::NOT:   return os << "!";
        case UnaryOperator::PLUS:  return os << "+";
        case UnaryOperator::MINUS: return os << "-";
    }

    assert(false);
}

enum class BinaryOperator
{
	ADD,        SUBTRACT,      MULTIPLY, DIVIDE,
	MODULO,
	LEFT_SHIFT, RIGHT_SHIFT,
	EQUAL,      NOT_EQUAL,
	LOWER,      LOWER_EQUAL,
	GREATER,    GREATER_EQUAL,
};

std::ostream& operator<<(std::ostream& os, const BinaryOperator op)
{
	switch (op)
    {
        case BinaryOperator::ADD:           return os << "+";
        case BinaryOperator::SUBTRACT:      return os << "-";
        case BinaryOperator::MULTIPLY:      return os << "*";
        case BinaryOperator::DIVIDE:        return os << "/";
        case BinaryOperator::MODULO:        return os << "%";
        case BinaryOperator::LEFT_SHIFT:    return os << "<<";
        case BinaryOperator::RIGHT_SHIFT:   return os << ">>";
        case BinaryOperator::EQUAL:         return os << "==";
        case BinaryOperator::NOT_EQUAL:     return os << "!=";
        case BinaryOperator::LOWER:         return os << "<";
        case BinaryOperator::LOWER_EQUAL:   return os << "<=";
        case BinaryOperator::GREATER:       return os << ">";
        case BinaryOperator::GREATER_EQUAL: return os << ">=";
    }

    assert(false);
}

typedef boost::variant<
	double, 
	int, 
	std::string
> Literal;

struct Identifier
{
	std::string name;
};
BOOST_FUSION_ADAPT_STRUCT(Identifier, (std::string, name))

struct UnaryOperation;
struct BinaryOperation;
struct FunctionCall;

typedef boost::variant<
	Literal, 
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
BOOST_FUSION_ADAPT_STRUCT(UnaryOperation, (Expression,rhs)(UnaryOperator,op))

struct BinaryOperation
{
	Expression rhs;
	BinaryOperator op;
	Expression lhs;

	BinaryOperation() {}
	BinaryOperation(Expression rhs, BinaryOperator op, Expression lhs) : rhs(rhs), op(op), lhs(lhs) {}
};
BOOST_FUSION_ADAPT_STRUCT(BinaryOperation, (Expression,rhs)(BinaryOperator,op)(Expression,lhs))

struct FunctionCall
{
	Identifier functionName;
	std::vector<Expression> args;
};
BOOST_FUSION_ADAPT_STRUCT(FunctionCall, (Identifier, functionName)(std::vector<Expression>, args))

struct Program
{
	std::vector<Expression> statements;
};
BOOST_FUSION_ADAPT_STRUCT(Program, (std::vector<Expression>, statements))

std::ostream& operator<<(std::ostream& os, const Expression& expr)
{
	os << "Expression ";
    struct v : boost::static_visitor<> {
        v(std::ostream& os) : os(os) {}
        std::ostream& os;

        void operator()(Literal         const& e) const { os << "(literal: "    << e                           << ")"; }
        void operator()(Identifier      const& e) const { os << "(identifier: " << e.name                      << ")"; }
        void operator()(UnaryOperation  const& e) const { os << "(unary op: "   << boost::fusion::as_vector(e) << ")"; }
        void operator()(BinaryOperation const& e) const { os << "(binary op: "  << boost::fusion::as_vector(e) << ")"; }
        void operator()(FunctionCall    const& e) const {
	        os << "(function call: " << e.functionName << "("; 
            if (e.args.size() > 0) os << e.args.front();
            for (auto it = e.args.begin() + 1; it != e.args.end(); it++) { os << ", " << *it; }
            os << ")";
        }
    };
    boost::apply_visitor(v(os), expr);
	return os;
}

std::ostream& operator<<(std::ostream& os, const Program& prog)
{
	os << "Program" << std::endl << "{" << std::endl;
	for (const Expression& expr : prog.statements) 
    { 
        std::cout << "\t" << expr << std::endl; 
    }
	os << "}" << std::endl;

	return os;
}

template<typename Iterator, typename Skipper>
struct BoltGrammar : qi::grammar<Iterator, Skipper, Program()>
{
	BoltGrammar() : BoltGrammar::base_type(start, "start")
	{
		using namespace qi::labels;

        equalOp.add
            ("==", BinaryOperator::EQUAL)
            ("!=", BinaryOperator::NOT_EQUAL);
        lowerGreaterOp.add
            ("<", BinaryOperator::LOWER)
            ("<=", BinaryOperator::LOWER_EQUAL)
            (">", BinaryOperator::GREATER)
            (">=", BinaryOperator::GREATER_EQUAL);
        shiftOp.add
            ("<<", BinaryOperator::LEFT_SHIFT)
            (">>", BinaryOperator::RIGHT_SHIFT);
        addSubOp.add
            ("+", BinaryOperator::ADD)
            ("-", BinaryOperator::SUBTRACT);
        multDivModOp.add
            ("*", BinaryOperator::MULTIPLY)
            ("/", BinaryOperator::DIVIDE)
            ("%", BinaryOperator::MODULO);

		equal        = lowerGreater [ _val=_1 ] >> -(equalOp        >> lowerGreater) [ _val = phx::construct<BinaryOperation>(_val, _1, _2) ];
		lowerGreater = shift        [ _val=_1 ] >> -(lowerGreaterOp >> shift)        [ _val = phx::construct<BinaryOperation>(_val, _1, _2) ];
		shift        = addSub       [ _val=_1 ] >> -(shiftOp        >> addSub)       [ _val = phx::construct<BinaryOperation>(_val, _1, _2) ];
		addSub       = multDivMod   [ _val=_1 ] >> -(addSubOp       >> multDivMod)   [ _val = phx::construct<BinaryOperation>(_val, _1, _2) ];
		multDivMod   = value        [ _val=_1 ] >> -(multDivModOp   >> value)        [ _val = phx::construct<BinaryOperation>(_val, _1, _2) ];

		start        = qi::eps >> -expression % ';';
		expression   = '(' >> expression >> ')' | equal | value;
		value        = identifier | literal;
		identifier   = qi::lexeme[ascii::char_("a-zA-Z") >> *ascii::char_("0-9a-zA-Z")];

        qi::real_parser<double, qi::strict_real_policies<double> > strict_double;

		literal      = quotedString | strict_double | qi::int_;
		quotedString = qi::lexeme['"' >> +(ascii::char_ - '"') >> '"'];

		qi::on_error<qi::fail>(start, std::cout << phx::val("Error! Expecting: ") << _4 << phx::val(" here: \"") << phx::construct<std::string>(_3, _2) << phx::val("\"") << std::endl);

        BOOST_SPIRIT_DEBUG_NODES((start)(expression)(identifier)(literal)(quotedString)
                (equal)(lowerGreater)(shift)(addSub)(multDivMod)(value)
                )
	}

	qi::symbols<char, BinaryOperator> equalOp, lowerGreaterOp, shiftOp, addSubOp, multDivModOp;
	qi::rule<Iterator, Skipper, Expression()>  equal,  lowerGreater,  shift,  addSub,  multDivMod;
	qi::rule<Iterator, Skipper, Expression()>  value;

	qi::rule<Iterator, Skipper, Program()>     start;
	qi::rule<Iterator, Skipper, Expression()>  expression;
	qi::rule<Iterator, Skipper, Identifier()>  identifier;
	qi::rule<Iterator, Skipper, Literal()>     literal;
	qi::rule<Iterator, Skipper, std::string()> quotedString;
};

typedef std::string::iterator Iterator;
typedef boost::spirit::ascii::space_type Skipper;

int main()
{
	BoltGrammar<Iterator, Skipper> grammar;

	std::string str("3; 4.2; \"lounge <c++>\"; 3 + 4;");

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
    
	return 0;
}