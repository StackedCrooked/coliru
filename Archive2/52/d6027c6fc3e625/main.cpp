/* Copyright (c) 2013 by Pierre Talbot
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

namespace ast{

    struct addTag{};
    struct subTag{};
    struct mulTag{};
    struct divTag{};

    template <class OpTag>
    struct binary_op;

    struct usub_op;

    typedef binary_op<addTag> add_op;
    typedef binary_op<subTag> sub_op;
    typedef binary_op<mulTag> mul_op;
    typedef binary_op<divTag> div_op;

    typedef long arithmetic_type;

    typedef boost::variant<
        arithmetic_type
        , boost::recursive_wrapper<add_op>
        , boost::recursive_wrapper<sub_op>
        , boost::recursive_wrapper<mul_op>
        , boost::recursive_wrapper<div_op>
        , boost::recursive_wrapper<usub_op>
    > expression;

    template <class OpTag>
    struct binary_op
    {
        typedef OpTag operation_type;

    expression left;
    expression right;

    binary_op(const expression& lhs, const expression& rhs)
    : left(lhs), right(rhs)
    {}

    binary_op() = default;
    binary_op(const binary_op&) = default;
    };

    // Unary -. (ex: -(4-6)=2)
    struct usub_op
    {
        expression expr;

        usub_op(const expression& expr)
        : expr(expr)
        {}

        usub_op() = default;
        usub_op(const usub_op&) = default;
    };

} // namespace ast

// Fusion AST adaptation.
BOOST_FUSION_ADAPT_STRUCT(
    ast::usub_op,
	(ast::expression, expr)
)

BOOST_FUSION_ADAPT_TPL_STRUCT(
	(OpTag),
	(ast::binary_op) (OpTag),
	(ast::expression, left)
	(ast::expression, right)
)

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace bs = boost::spirit;
namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

// Grammar definition, define a little part of the SQL language.
template <typename Iterator>
struct grammar 
	: qi::grammar<Iterator, ast::expression()>
{
	typedef Iterator iterator_type;

	grammar() : grammar::base_type(expression, "arithmetic expression")
    {
        /**
        * These rules permit the automatic generation of semantic rules (AST
        * creation) because they are typed. (see the parser.hpp to look at the
        * type.)
        */
        expression %= add_expr | sub_expr | term;
        term       %= mul_expr | div_expr | factor;

        factor %=  
            qi::ulong_
            | ('(' >> expression >> ')')
            | neg_expr
            | ('+' >> factor)
            ;

        add_expr %= (term    >> '+'  >> expression) ;
        sub_expr %= (term    >> '-'  >> expression) ;
        mul_expr %= (factor  >> '*'  >> term)       ;
        div_expr %= (factor  >> '\\' >> term)       ;
        neg_expr %= ('-' >> factor) ;

        BOOST_SPIRIT_DEBUG_NODES(
                (expression)
                (term)
                (factor)
                (add_expr)
                (sub_expr)
                (mul_expr)
                (div_expr)
                (neg_expr)
            );

        return;
        using namespace qi::labels;
        qi::on_error<qi::fail>
            (
                expression,
                std::cout
                << phx::val("Error! Expecting ")
                << bs::_4                               // what failed?
                << phx::val(" here: \"")
                << phx::construct<std::string>(bs::_3, bs::_2)   // iterators to error-pos, end
                << phx::val("\"")
                << std::endl
            );
    }

private:
	ast::expression arithmetic_expr;

    template <typename Arg> using rule = qi::rule<iterator_type, Arg()>;
	rule<ast::expression> expression;
	rule<ast::add_op>     add_expr;
	rule<ast::sub_op>     sub_expr;
	rule<ast::mul_op>     mul_expr;
	rule<ast::div_op>     div_expr;
	rule<ast::usub_op>    neg_expr;
	rule<ast::expression> term;
	rule<ast::expression> factor;
};

// iterator type used to expose the underlying input stream
typedef std::string::const_iterator iterator_type;

// this is the type of the grammar to parse
typedef grammar<iterator_type> grammar_type;

template struct grammar<iterator_type>;

namespace /* static */ {

struct evaluator : boost::static_visitor<ast::arithmetic_type>
{
  int operator()(ast::arithmetic_type value) const {
    return value;
  }

  int operator()(const ast::add_op& binary) const {
    return boost::apply_visitor(*this, binary.left)
         + boost::apply_visitor(*this, binary.right);
  }

  int operator()(const ast::sub_op& binary) const
  {
    return boost::apply_visitor(*this, binary.left)
         - boost::apply_visitor(*this, binary.right);
  }

  int operator()(const ast::mul_op& binary) const {
    return boost::apply_visitor(*this, binary.left)
         * boost::apply_visitor(*this, binary.right);
  }

  int operator()(const ast::div_op& binary) const {
    ast::arithmetic_type right_value = boost::apply_visitor(*this, binary.right);
    if(right_value == 0)
        throw std::logic_error("Division by zero detected.");
    return boost::apply_visitor(*this, binary.left)
         / right_value;
  }

  int operator()(const ast::usub_op& usub) const
  {
    return - boost::apply_visitor(*this, usub.expr);
  }
};

} // namespace /* static */

int eval_expression(const std::string& expr)
{
  static const grammar_type parser;

  // At this point we generate the iterator pair
  iterator_type first(expr.begin());
  iterator_type last(expr.end());

  ast::expression arith_ast;
  bool r = boost::spirit::qi::parse(first, last, parser, arith_ast);
  if (r && first == last)
  {
    static const evaluator _evaluator;
    return boost::apply_visitor(_evaluator, arith_ast);
  }
  else
  {
    throw std::invalid_argument("The arithmetic expression is malformed.\n");
  }
}

int main()
{
    assert(42 == eval_expression("8*4+10"));
}
