#define BOOST_SPIRIT_QI_DEBUG

#include <vector>
#include <list>
#include <boost/variant/recursive_variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace client { namespace ast
{
    struct tagged { int id; };

    struct nil {};
    struct unary;
    struct function_call;
    struct expression;

    struct identifier : tagged
    {
        identifier(std::string const& name = "") : name(name) {}
        std::string name;
    };

    typedef boost::variant<
            nil
          , bool
          , unsigned int
          , identifier
          , boost::recursive_wrapper<unary>
          , boost::recursive_wrapper<function_call>
          , boost::recursive_wrapper<expression>
        >
    operand;

    enum optoken
    {
        op_plus,
        op_minus,
        op_times,
        op_divide,
        op_positive,
        op_negative,
        op_not,
        op_equal,
        op_not_equal,
        op_less,
        op_less_equal,
        op_greater,
        op_greater_equal,
        op_and,
        op_or
    };

    struct unary
    {
        optoken operator_;
        operand operand_;
    };

    struct operation
    {
        optoken operator_;
        operand operand_;
    };

    struct function_call
    {
        identifier function_name;
        std::list<operand> args;
    };

    struct expression
    {
        operand first;
        std::list<operation> rest;
    };

    // print functions for debugging
    inline std::ostream& operator<<(std::ostream& out, nil) { out << "nil"; return out; }
    inline std::ostream& operator<<(std::ostream& out, identifier const& id) { out << id.name; return out; }
} }

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::unary,
    (client::ast::optoken, operator_)
    (client::ast::operand, operand_)
)

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::operation,
    (client::ast::optoken, operator_)
    (client::ast::operand, operand_)
)

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::function_call,
    (client::ast::identifier, function_name)
    (std::list<client::ast::operand>, args)
)

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::expression,
    (client::ast::operand, first)
    (std::list<client::ast::operation>, rest)
)

namespace client { namespace parser
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    ///////////////////////////////////////////////////////////////////////////////
    // there's a bug in attr_cast with compound sub-expressions, this is the
    // workaround
    template <typename Parser>
        auto as_expr(Parser const& p) -> decltype(qi::attr_cast<ast::expression, ast::expression>(boost::proto::deep_copy(p)))
        {
            return qi::attr_cast<ast::expression, ast::expression>(boost::proto::deep_copy(p));
        }

    ///////////////////////////////////////////////////////////////////////////////
    //  The expression grammar
    ///////////////////////////////////////////////////////////////////////////////
    template <typename Iterator>
    struct expression : qi::grammar<Iterator, ast::operand(), qi::space_type >
    {
        expression()
        : expression::base_type(expr)
    {
	    using namespace qi;
	    using boost::phoenix::function;

	    ///////////////////////////////////////////////////////////////////////
	    // Tokens
	    logical_or_op.add
		("||", ast::op_or)
		;

	    logical_and_op.add
		("&&", ast::op_and)
		;

	    equality_op.add
		("==", ast::op_equal)
		("!=", ast::op_not_equal)
		;

	    relational_op.add
		("<",  ast::op_less)
		("<=", ast::op_less_equal)
		(">",  ast::op_greater)
		(">=", ast::op_greater_equal)
		;

	    additive_op.add
		("+",  ast::op_plus)
		("-",  ast::op_minus)
		;

	    multiplicative_op.add
		("*",  ast::op_times)
		("/",  ast::op_divide)
		;

	    unary_op.add
		("+",  ast::op_positive)
		("-",  ast::op_negative)
		("!",  ast::op_not)
		;

	    keywords.add
		("true")
		("false")
		("if") ("else") ("while")
		("int") ("void") ("return")
		;

	    ///////////////////////////////////////////////////////////////////////
	    // Main expression grammar
	    expr = logical_or_expr.alias() ;

	    logical_or_expr     = as_expr(logical_and_expr    >> +(logical_or_op     > logical_and_expr)) 
                            | logical_and_expr
                            ;
	    logical_and_expr    = as_expr(equality_expr       >> +(logical_and_op    > equality_expr)) 
                            | equality_expr
                            ;
	    equality_expr       = as_expr(relational_expr     >> +(equality_op       > relational_expr))
                            | relational_expr
                            ;
	    relational_expr     = as_expr(additive_expr       >> +(relational_op     > additive_expr))
                            | additive_expr
                            ;
	    additive_expr       = as_expr(multiplicative_expr >> +(additive_op       > multiplicative_expr))
                            | multiplicative_expr
                            ;
	    multiplicative_expr = as_expr(unary_expr          >> *(multiplicative_op > unary_expr)) 
                            | attr_cast<ast::operand, ast::operand> (unary_expr)
                            ;

	    unary_expr =
		    primary_expr
		|   (unary_op > unary_expr)
		;

	    primary_expr =
		    uint_
		|   function_call
		|   identifier
		|   bool_
		|   ('(' > expr > ')')
		;

	    function_call =
		    (identifier >> '(')
		>   argument_list
		>   ')'
		;

	    argument_list = -(expr % ',');

	    identifier =
		    !lexeme[keywords >> !(alnum | '_')]
		>>  raw[lexeme[(alpha | '_') >> *(alnum | '_')]]
		;

	    ///////////////////////////////////////////////////////////////////////
	    // Debugging and error handling and reporting support.
	    BOOST_SPIRIT_DEBUG_NODES(
		(expr)
		(logical_or_expr)
		(logical_and_expr)
		(equality_expr)
		(relational_expr)
		(additive_expr)
		(multiplicative_expr)
		(unary_expr)
		(primary_expr)
		(function_call)
		(argument_list)
		(identifier)
	    );

	    // TODO error_handling
	}

        qi::rule<Iterator, ast::operand(), qi::space_type >
            expr
	    ;

        qi::rule<Iterator, ast::operand(), qi::space_type >
            equality_expr, relational_expr,
            logical_or_expr, logical_and_expr,
            additive_expr, multiplicative_expr
            ;

        qi::rule<Iterator, ast::operand(), qi::space_type >
            unary_expr, primary_expr
            ;

        qi::rule<Iterator, ast::function_call(), qi::space_type >
            function_call
            ;

        qi::rule<Iterator, std::list<ast::operand>(), qi::space_type >
            argument_list
            ;

        qi::rule<Iterator, std::string(), qi::space_type >
            identifier
            ;

        qi::symbols<char, ast::optoken>
            logical_or_op, logical_and_op,
            equality_op, relational_op,
            additive_op, multiplicative_op, unary_op
            ;

        qi::symbols<char>
            keywords
            ;
    };
}}

int main()
{
    namespace qi = boost::spirit::qi;

    std::string const input = "42";
    typedef std::string::const_iterator iterator_type;
    iterator_type iter = input.begin();
    iterator_type end  = input.end();

    client::parser::expression<iterator_type> parser;  

    client::ast::operand parsed;
    bool success = phrase_parse(iter, end, parser, qi::space, parsed);

    std::cout << "-------------------------\n";

    if (success && iter == end)
    {
    }
    else
    {
        std::cout << "Parse failure\n";
    }
}

