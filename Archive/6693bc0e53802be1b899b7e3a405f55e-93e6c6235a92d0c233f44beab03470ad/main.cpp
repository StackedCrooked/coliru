#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/function/adapt_function.hpp>

#include <cassert>

namespace phx = boost::phoenix;
namespace qi  = boost::spirit::qi;
namespace lex = boost::spirit::lex;

#ifndef _AST_HPP
#define _AST_HPP

#include <string>

namespace ast
{
    //--------------------//
    // Abstract AST Types //
    //--------------------//
    struct expression
    {
        protected:
            expression() {}
        public:
            virtual ~expression() {}
    };

    //--------------------//
    // Concrete AST Types //
    //--------------------//
    // Binary operators
    struct binop
    {
        protected:
            binop() {}
        public:
            virtual ~binop() {} 
    };
    // Arithmetic operators
    struct binop_plus final : binop {};
    struct binop_minus final : binop {};
    struct binop_times final : binop {};
    struct binop_divide final : binop {};

    struct binop_expression final : expression
    {
        binop_expression(const expression* exp1, const binop* operatur, const expression* exp2)
            : exp1(exp1), operatur(operatur), exp2(exp2)
        {
        }

        const expression* exp1;
        const binop* operatur;
        const expression* exp2;
    };

    struct unary_minus_expression final : expression
    {
        unary_minus_expression(const expression* exp)
            : exp(exp)
        {
        }

        const expression* exp;
    };

    struct integer_constant final : expression
    {
        // "1", "1231"
        integer_constant(std::string value)
            : value(value)
        {
        }

        std::string value;
    };
}

#endif //_AST_HPP


enum tokenids 
{
    IDANY = lex::min_token_id + 10,
    LEFT_PAREN,
    RIGHT_PAREN,
    PLUS,
    MINUS,
    MULTIPLICATION,
    DIVISION,
    NUMBER
};

ast::expression* build_binop_expression(ast::expression* t1, ast::binop* operatur, ast::expression* t2)
{
    return nullptr;
}
BOOST_PHOENIX_ADAPT_FUNCTION(ast::expression*, build_binop_expression_, build_binop_expression, 3)

ast::expression* build_unary_minus_expression(ast::expression* t)
{
    return nullptr;
}
BOOST_PHOENIX_ADAPT_FUNCTION(ast::expression*, build_unary_minus_expression_, build_unary_minus_expression, 1)

ast::expression* build_integer_constant_expression(std::string str)
{
    return new ast::integer_constant(str);
}
BOOST_PHOENIX_ADAPT_FUNCTION(ast::expression*, build_integer_constant_expression_, build_integer_constant_expression, 1)

template <typename Lexer>
struct strip_comments_tokens : lex::lexer<Lexer>
{
    strip_comments_tokens() 
      : strip_comments_tokens::base_type(lex::match_flags::match_default)
    {
    	left_paren = "\\("; 
		right_paren = "\\)";
		plus = "\\+";
		minus = "-";
		multiplication = "\\*";
        division = "\\/";
        number = "x";

        this->self.add
            (left_paren, LEFT_PAREN) 
            (right_paren, RIGHT_PAREN)
            (plus, PLUS)
            (minus, MINUS)
            (multiplication, MULTIPLICATION)
            (division, DIVISION)
            (number, NUMBER)
        ;
    }
	lex::token_def<lex::omit> left_paren, right_paren, plus, minus, multiplication, division;
    lex::token_def<std::string> number;
};

///////////////////////////////////////////////////////////////////////////////
//  Grammar definition
///////////////////////////////////////////////////////////////////////////////
template <typename Iterator>
struct strip_comments_grammar : qi::grammar<Iterator, ast::expression*()>
{
    template <typename TokenDef>
    strip_comments_grammar(TokenDef const& tok)
      : strip_comments_grammar::base_type(plus_factor)
    {
        start = expression [ qi::_val = qi::_1 ]
              ;

        expression = term >> tok.plus  >> term [ qi::_val = qi::_1 ] // [ qi::_val = build_binop_expression_(qi::_1, phoenix::new_<ast::binop_plus>(), qi::_2) ]
                   | term >> tok.minus >> term [ qi::_val = qi::_1 ] // [ qi::_val = build_binop_expression_(qi::_1, phoenix::new_<ast::binop_minus>(), qi::_2) ]
                   | term                        [ qi::_val = qi::_1 ]
                   ;

        term = factor >> tok.multiplication >> factor   [ qi::_val = qi::_1 ] // [ qi::_val = build_binop_expression_(qi::_1, phoenix::new_<ast::binop_times>(), qi::_2) ]
             | factor >> tok.division       >> factor   [ qi::_val = qi::_1 ] // [ qi::_val = build_binop_expression_(qi::_1, phoenix::new_<ast::binop_divide>(), qi::_2) ]
             | factor                                     [ qi::_val = qi::_1 ]
             ;

        factor = /*tok.minus >> plus_factor                 [ qi::_val = qi::_2 ] // [ qi::_val = build_unary_minus_expression_(qi::_2) ]
               |*/ plus_factor                              [ qi::_val = qi::_1 ]
               ;
               
        plus_factor = tok.number                        [ qi::_val = build_integer_constant_expression_(qi::_1) ]
                    | tok.left_paren >> expression >> tok.right_paren [ qi::_val = qi::_1 ] // qi::_1 or qi::_2?
                    ;
    } 
    qi::rule<Iterator, ast::expression*()> start;
    qi::rule<Iterator, ast::expression*()> expression;
    qi::rule<Iterator, ast::expression*()> term;
    qi::rule<Iterator, ast::expression*()> factor;
    qi::rule<Iterator, ast::expression*()> plus_factor;
};

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // iterator type used to expose the underlying input stream
    typedef std::string::iterator base_iterator_type;

    // lexer type
    typedef 
        lex::lexertl::lexer<lex::lexertl::token<base_iterator_type,boost::mpl::vector<std::string> > > //you need to add an mpl::vector of the types of the attributes that your lexer exposes ( in this case simply char )
    lexer_type;

    // iterator type exposed by the lexer 
    typedef strip_comments_tokens<lexer_type>::iterator_type iterator_type;

    // now we use the types defined above to create the lexer and grammar
    // object instances needed to invoke the parsing process
    strip_comments_tokens<lexer_type> strip_comments;           // Our lexer
    strip_comments_grammar<iterator_type> g (strip_comments);   // Our parser 

    // Parsing is done based on the the token stream, not the character 
    // stream read from the input.
    
    std::string str = "x";
    base_iterator_type first = str.begin();
    bool b = lex::tokenize_and_parse(first, str.end(), strip_comments, g);
    
    if(b)
    {
        std::cout << "IT SUCCEDDED!";
    }
    else
    {
        std::cout << "IT FAILED";
    }
    
    return 0;
}
