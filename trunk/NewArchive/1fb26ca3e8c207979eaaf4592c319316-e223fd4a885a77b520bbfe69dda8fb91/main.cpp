#define BOOST_VARIANT_MINIMIZE_SIZE
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
// #include <boost/spirit/include/phoenix.hpp>
#include <iostream>
#include <string>

namespace qi  = boost::spirit::qi;
namespace lex = boost::spirit::lex;

template <typename Lexer>
struct token_list : lex::lexer<Lexer>
{
    token_list()
    {
        noun        = "birds|cats";    
        verb        = "fly|meow";
        conjunction = "and";

        this->self.add
            (noun)         
            (verb) 
            (conjunction)
        ;
    }

    lex::token_def<std::string> noun, verb, conjunction;
};

template <typename Iterator>
struct Grammar : qi::grammar<Iterator>
{
    template <typename TokenDef>
    Grammar(TokenDef const& tok) : Grammar::base_type(sentence)
    {
        sentence = 
              (tok.noun >> tok.verb) 
          >> *(tok.conjunction >> sentence) >> qi::eoi
          ;
    }
    qi::rule<Iterator> sentence;
};

int main()
{
    typedef std::string::const_iterator It;
    typedef lex::lexertl::token<It, boost::mpl::vector<std::string>> token_type;
    typedef lex::lexertl::lexer<token_type> lexer_type;
    typedef token_list<lexer_type>::iterator_type iterator_type;

    token_list<lexer_type> word_count;         
    Grammar<iterator_type> g(word_count); 

    //std::string str = "birdsfly"; 
    const std::string str = "birds fly";

    It first = str.begin();
    It last  = str.end();

    bool r = lex::tokenize_and_parse(first, last, word_count, g);

    if (r) {
        std::cout << "Parsing passed"<< "\n";
    }
    else {
        std::string rest(first, last);
        std::cerr << "Parsing failed\n" << "stopped at: \"" << rest << "\"\n";
    }
}

