#define BOOST_RESULT_OF_USE_DECLTYPE
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/phoenix/function/adapt_callable.hpp>

namespace qi  = boost::spirit::qi;
namespace lex = boost::spirit::lex;
namespace phx = boost::phoenix;

///////////////////////////////////////////////////////////////////////////
// irrelevant for question: needed this locally to make it work with my boost
// version
namespace detail {
    struct count {
        template<class It1, class It2, class T> struct result { typedef ptrdiff_t type; };
        template<class It1, class It2, class T>
            typename result<It1, It2, T>::type operator()(It1 f, It2 l, T const& x) const {
                return std::count(f, l, x);
            }
    };
}

BOOST_PHOENIX_ADAPT_CALLABLE(count, detail::count, 3)
///////////////////////////////////////////////////////////////////////////

template <typename LexerT>
   class Tokens: public lex::lexer<LexerT>
   {

      public:
         Tokens():
            lineNo_(1)
         {
            using lex::_start;
            using lex::_end;
            using lex::_pass;
            using phx::ref;

            // macros
            this->self.add_pattern
               ("EXP",     "(e|E)(\\+|-)?\\d+")
               ("SUFFIX",  "[yzafpnumkKMGTPEZY]")
               ("INTEGER", "-?\\d+")
               ("FLOAT",    "-?(((\\d+)|(\\d*\\.\\d+)|(\\d+\\.\\d*))({EXP}|{SUFFIX})?)")
               ("SYMBOL",  "[a-zA-Z_?@](\\w|\\?|@)*")
               ("STRING",  "\\\"([^\\\"]|\\\\\\\")*\\\"");

            // whitespaces and comments
            whitespaces_ = "\\s+";
            comments_    = "(;[^\\n]*\\n)|(\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/)";

            // literals
            integer_ = "{INTEGER}";
            float_   = "{FLOAT}";
            symbol_  = "{SYMBOL}";
            string_  = "{STRING}";

            // operators
            quote_         = "'";
            backquote_     = '`';

            // ... other tokens

            // whitespace and comment rules
            //this->self.add(whitespaces_, 1001)
                          //(comments_,    1002);
            this->self = whitespaces_ [phx::ref(lineNo_) += count(_start, _end, '\n'), _pass = lex::pass_flags::pass_ignore]
                       | comments_    [phx::ref(lineNo_) += count(_start, _end, '\n'), _pass = lex::pass_flags::pass_ignore];

            // literal rules
            this->self += integer_ | float_ | string_ | symbol_;
            // this->self += ... other tokens
         }

         template <typename TokIter>
         std::string nameof(TokIter it)
         {
             if (it->id() == whitespaces_.id()) return "whitespaces_";
             if (it->id() == comments_.id())    return "comments_";
             if (it->id() == integer_.id())     return "integer_";
             if (it->id() == float_.id())       return "float_";
             if (it->id() == symbol_.id())      return "symbol_";
             if (it->id() == string_.id())      return "string_";

             if (it->id() == quote_.id())       return "quote_";
             if (it->id() == backquote_.id())   return "backquote_";
             return "other";
         }

         ~Tokens() {}

         size_t lineNo() { return lineNo_; }


      private:
         // ignored tokens
         lex::token_def</*lex::omit*/> whitespaces_, comments_;

         // literal tokens
         lex::token_def<int>          integer_;
         lex::token_def<std::string>  float_, symbol_, string_;

         // operator tokens
         lex::token_def<> quote_, backquote_;
         // ... other token definitions of type lex::token_def<>

         // current line number
         size_t lineNo_;
   };

int main()
{
    const std::string str = "symbol \"string\" \n"
        "this /* is a comment */\n"
        "31415926E-7 123";

    typedef lex::lexertl::token<char const*> token_type;
    typedef lex::lexertl::actor_lexer<token_type> lexer_type;

    Tokens<lexer_type> toklexer;

    char const* first = str.c_str();
    char const* last = &first[str.size()];

    lexer_type::iterator_type iter = toklexer.begin(first, last);
    lexer_type::iterator_type end = toklexer.end();

    while (iter != end && token_is_valid(*iter))
    {
        std::cout << "Token: " << 
           (iter->id() - lex::min_token_id) << ": " << 
           toklexer.nameof(iter) << " ('" << iter->value() << "')\n";
        ++iter;
    }

    if (iter == end) { std::cout << "lineNo: " << toklexer.lineNo() << "\n"; }
    else {
        std::string rest(first, last);
        std::cout << "Lexical analysis failed\n" << "stopped at: \""
            << rest << "\"\n";
    }
    return 0;
}