#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/function/adapt_function.hpp>

#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/include/at_c.hpp>

#include <cassert>

namespace phx = boost::phoenix;
namespace qi  = boost::spirit::qi;
namespace lex = boost::spirit::lex;

enum tokenids 
{
    IDANY = lex::min_token_id + 10,
    LEFT_PAREN,
    RIGHT_PAREN,
    CHARACTER
};

// HERE:
// This prototype doesn't seem usable, as the second argument produces the error;
// error: type 'char' cannot be used prior to '::' because it has no members
//    MEMBER_TYPE_OF(iterator);
char build_paren(char c1, char c2, char c3)/*boost::iterator_range<std::string::iterator> a, char c, boost::iterator_range<std::string::iterator> b*/
{
    std::cout << "LL" << std::endl;
    std::cout << c1 << std::endl;
    std::cout << c2 << std::endl;
    std::cout << c3 << std::endl;
    
    return 'X';
}

BOOST_PHOENIX_ADAPT_FUNCTION(char, build_paren_, build_paren, 3)

char build_character(char c)
{
    return c;
}

BOOST_PHOENIX_ADAPT_FUNCTION(char, build_character_, build_character, 1)

template <typename Lexer>
struct strip_comments_tokens : lex::lexer<Lexer>
{
    strip_comments_tokens() 
      : strip_comments_tokens::base_type(lex::match_flags::match_default)
    {
        this->self.add
            ('(', LEFT_PAREN)
            (')', RIGHT_PAREN)
            ("-", CHARACTER)
        ;
    }
};

///////////////////////////////////////////////////////////////////////////////
//  Grammar definition
///////////////////////////////////////////////////////////////////////////////
template <typename Iterator>
struct strip_comments_grammar : qi::grammar<Iterator>
{
    template <typename TokenDef>
    strip_comments_grammar(TokenDef const& tok)
      : strip_comments_grammar::base_type(start)
    {
        start = paren;
        
        paren = (qi::token(LEFT_PAREN) >> character >> qi::token(RIGHT_PAREN)) [ qi::_val = build_paren_(*phx::begin(qi::_1), *phx::begin(qi::_2), *phx::begin(qi::_3)) ]
              ;
        character = qi::token(CHARACTER) [ qi::_val = build_character_(*phx::begin(qi::_1)) ]
              ;
    }
    
    qi::rule<Iterator> start;
    qi::rule<Iterator, char()> paren;
    qi::rule<Iterator, char()> character;
};

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // iterator type used to expose the underlying input stream
    typedef std::string::iterator base_iterator_type;

    // lexer type
    typedef 
        lex::lexertl::lexer<lex::lexertl::token<base_iterator_type> > 
    lexer_type;

    // iterator type exposed by the lexer 
    typedef strip_comments_tokens<lexer_type>::iterator_type iterator_type;

    // now we use the types defined above to create the lexer and grammar
    // object instances needed to invoke the parsing process
    strip_comments_tokens<lexer_type> strip_comments;           // Our lexer
    strip_comments_grammar<iterator_type> g (strip_comments);   // Our parser 

    // Parsing is done based on the the token stream, not the character 
    // stream read from the input.
    
    std::string str = "(-)";
    base_iterator_type first = str.begin();
    lex::tokenize_and_parse(first, str.end(), strip_comments, g);
    
    return 0;
}
