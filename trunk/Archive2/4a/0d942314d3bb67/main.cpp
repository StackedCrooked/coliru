#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <fstream>
#include <sstream>    
#include <boost/lexical_cast.hpp>

namespace lex = boost::spirit::lex;

template <typename Lexer>
struct tokens : lex::lexer<Lexer>
{
    tokens() 
    {
        pound_   = "#";
        define_  = "define";
        if_      = "if";
        else_    = "else";
        endif_   = "endif";
        ifdef_   = "ifdef";
        ifndef_  = "ifndef";
        defined_ = "defined";
        keyword_ = "for|break|continue|while|do|switch|case|default|if|else|return|goto|throw|catch"
                   "static|volatile|auto|void|int|char|signed|unsigned|long|double|float|"
                   "delete|new|virtual|override|final|"
                   "typename|template|using|namespace|extern|\"C\"|"
                   "friend|public|private|protected|"
                   "class|struct|enum|"
                   "register|thread_local|noexcept|constexpr";
        scope_   = "::";
        dot_     = '.';
        arrow_   = "->";
        star_    = '*';
        popen_   = '(';
        pclose_  = ')';
        bopen_   = '{';
        bclose_  = '}';
        iopen_   = '[';
        iclose_  = ']';
        colon_   = ':';
        semic_   = ';';
        comma_   = ',';
        tern_q_  = '?';
        relop_   = "==|!=|<=|>=|<|>";
        assign_  = '=';
        incr_    = "\\+\\+";
        decr_    = "--";
        binop_   = "[-+/%&|^]|>>|<<";
        unop_    = "[-+~!]";

        real_    = "[-+]?[0-9]+(e[-+]?[0-9]+)?f?";
        int_     = "[-+]?[0-9]+";
        identifier_ = "[a-zA-Z_][a-zA-Z0-9_]*";

        ws_            = "[ \\t\\r\\n]";
        line_comment_  = "\\/\\/.*?[\\r\\n]";
        block_comment_ = "\\/\\*.*?\\*\\/";

        this->self.add_pattern
            ("SCHAR", "\\\\(x[0-9a-fA-F][0-9a-fA-F]|[\\\\\"'0tbrn])|[^\"\\\\'\\r\\n]")
            ;
        string_lit = "\\\"('|{SCHAR})*?\\\"";
        char_lit   = "'(\\\"|{SCHAR})'";

        this->self += 
              pound_ | define_ | if_ | else_ | endif_ | ifdef_ | ifndef_ | defined_
            | keyword_ | scope_ | dot_ | arrow_ | star_ | popen_ | pclose_ | bopen_ | bclose_ | iopen_ | iclose_ | colon_ | semic_ | comma_ | tern_q_
            | relop_ | assign_ | incr_ | decr_ | binop_ | unop_
            | int_ | real_ | identifier_ | string_lit | char_lit
            // ignore whitespace and comments
            | ws_           [ lex::_pass = lex::pass_flags::pass_ignore ]
            | line_comment_ [ lex::_pass = lex::pass_flags::pass_ignore ]
            | block_comment_[ lex::_pass = lex::pass_flags::pass_ignore ] 
            ;
    }

  private:
    lex::token_def<> pound_, define_, if_, else_, endif_, ifdef_, ifndef_, defined_;
    lex::token_def<> keyword_, scope_, dot_, arrow_, star_, popen_, pclose_, bopen_, bclose_, iopen_, iclose_, colon_, semic_, comma_, tern_q_;
    lex::token_def<> relop_, assign_, incr_, decr_, binop_, unop_;
    lex::token_def<int> int_;
    lex::token_def<double> real_;
    lex::token_def<> identifier_, string_lit, char_lit;
    lex::token_def<lex::omit> ws_, line_comment_, block_comment_;
};
struct token_value : boost::static_visitor<std::string>
{
    template <typename... T> // the token value can be a variant over any of the exposed attribute types
    std::string operator()(boost::variant<T...> const& v) const {
        return boost::apply_visitor(*this, v);
    }

    template <typename T> // the default value is a pair of iterators into the source sequence
    std::string operator()(boost::iterator_range<T> const& v) const {
        return { v.begin(), v.end() };
    }

    template <typename T>
    std::string operator()(T const& v) const { 
        // not taken unless used in Spirit Qi rules, I guess
        return std::string("attr<") + typeid(v).name() + ">(" + boost::lexical_cast<std::string>(v) + ")";
    }
};

struct process_token
{
    template <typename T>
    bool operator()(T const& token) const {
        std::cout << '[' /*<< token.id() << ":" */<< print(token.value()) << "]";
        return true;
    }

    token_value print;
};

int main()
{
    typedef boost::spirit::istream_iterator It;
    typedef lex::lexertl::token<It, boost::mpl::vector<int, double>, boost::mpl::true_ > token_type;
    tokens<lex::lexertl::actor_lexer<token_type> > lexer;

    std::ifstream ifs("main.cpp");
    ifs >> std::noskipws;
    It first(ifs), last;
    bool ok = lex::tokenize(first, last, lexer, process_token());

    std::cout << "\nTokenization " << (ok?"succeeded":"failed") << "; remaining input: '" << std::string(first,last) << "'\n";
}
