#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp> // for the parser expression *strip_comments.hello

namespace lex = boost::spirit::lex;
namespace phx = boost::phoenix;

template <typename Lexer>
struct strip_comments_tokens : lex::lexer<Lexer> {
    strip_comments_tokens() 
      : strip_comments_tokens::base_type(lex::match_flags::match_default)
    {
        ccomment   = "\\/\\*.*\\*\\/";
        hello      = "hello"; // why not "."?

        this->self += 
             ccomment [ lex::_pass = lex::pass_flags::pass_ignore ]
  // IDEA: | lex::token_def<char>(".") // to just accept anything
           | hello
           ;
    }

    lex::token_def<lex::omit>   ccomment;
    lex::token_def<std::string> hello;
};

int main() {
    typedef std::string::const_iterator base_iterator_type;
    typedef lex::lexertl::actor_lexer<
                lex::lexertl::token<base_iterator_type/*, boost::mpl::vector<char, std::string>, boost::mpl::false_*/>
            > lexer_type;

    strip_comments_tokens<lexer_type> strip_comments;         // Our lexer

    std::string const str("hello/*hello*/hello");
    std::string stripped;

    base_iterator_type first = str.begin();
    bool r = lex::tokenize_and_parse(first, str.end(), strip_comments, *strip_comments.hello, stripped);

    if (r)
        std::cout << "\nStripped: '" << stripped << "'\n";
    else
        std::cout << "Failed: '" << std::string(first, str.end()) << "'\n";
}
