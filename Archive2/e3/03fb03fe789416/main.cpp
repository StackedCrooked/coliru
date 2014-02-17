//#define BOOST_SPIRIT_LEXERTL_DEBUG
//#define BOOST_SPIRIT_DEBUG

#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>

namespace qi  = boost::spirit::qi;
namespace lex = boost::spirit::lex;

struct Data
{
    std::string label;
    int value;

    friend std::ostream& operator<<(std::ostream& os, Data const& d) {
        return os << "[label:'" << d.label << "', value:" << d.value << "]";
    }
};

BOOST_FUSION_ADAPT_STRUCT(Data, (std::string, label)(int, value))

template <typename Lexer>
    struct mylexer_t : lex::lexer<Lexer>
{
    mylexer_t()
    {
        ident       = "[a-zA-Z][a-zA-Z0-9_]*";
        open_label  = '\''; // descriptive names; also:
        close_label = '\''; // can't add same token to 2 states

        paren_open  = '(';
        paren_close = ')';
        integer     = "[-+]?[0-9]+";

        whitespace  = "[ \\t\\b\\f\\r\\n]";
        other       = ".";

        string_chars = "(\\\\'|[^$'])+"; // allowing escaped ' too

        this->self = ident
                   | open_label [ lex::_state = "STRING" ]
                   | whitespace [ lex::_pass = lex::pass_flags::pass_ignore ]
                   | paren_open
                   | paren_close
                   | integer
                   | other // last
                   ;

        this->self("STRING") =
              string_chars
            | close_label  [ lex::_state = "INITIAL" ]
              // anything else
            | lex::token_def<>(".") [ lex::_pass = lex::pass_flags::pass_fail, lex::_state = "INITIAL" ]
            ;
    }

    lex::token_def<int>
        integer;

    lex::token_def<std::string>
        ident, string_chars;

    lex::token_def<lex::omit>
        open_label, close_label, paren_open, paren_close,
        whitespace, other;
};

template <typename Iterator> struct my_grammar
    : public qi::grammar<Iterator, Data() >
{
    typedef my_grammar<Iterator> This;

    template <typename TokenDef>
        my_grammar(TokenDef const& tok) : my_grammar::base_type(_start)
    {
        _ident = tok.ident;
        _label = tok.open_label > tok.string_chars > tok.close_label;
        _value = tok.integer;
        _pair  = _label > tok.paren_open > _value > tok.paren_close;
        _start = qi::omit[*_ident] >> _pair;

        BOOST_SPIRIT_DEBUG_NODES((_label)(_start)(_pair)(_ident)(_value));
    }

  private:
    qi::rule<Iterator, int()> _value;
    qi::rule<Iterator, std::string()> _label, _ident;
    qi::rule<Iterator, Data()> _pair, _start;
};

namespace /* */ {

    std::string safechar(char ch)
    {
        std::string s;
        switch (ch)
        {
            case '\t': s += "\\t"; break;
            case '\0': s += "\\0"; break;
            case '\r': s += "\\r"; break;
            case '\n': s += "\\n"; break;
            default:
                s += ch;
        }
        return s;
    }

    template <typename... T>
        std::string showtoken(const boost::variant<T...>& value)
    {
        std::ostringstream oss;
        auto const& range = boost::get<boost::iterator_range<const char*> >(value);
        oss << '[';
        std::transform(range.begin(), range.end(), std::ostream_iterator<std::string>(oss), safechar);
        oss << ']';
        return oss.str();
    }
}

boost::optional<Data> do_parse(const std::string& v)
{
    char const *first = &v[0];
    char const *last = first+v.size();

    typedef lex::lexertl::token<char const*, boost::mpl::vector<int, std::string> > token_type;
    typedef lex::lexertl::actor_lexer<token_type> lexer_type;

    typedef mylexer_t<lexer_type>::iterator_type iterator_type;
    try
    {
        static mylexer_t<lexer_type> mylexer;
        static my_grammar<iterator_type> parser(mylexer);

        auto iter = mylexer.begin(first, last);
        auto end = mylexer.end();

        Data data;
        bool r = qi::parse(iter, end, parser, data);

        if (iter != end)
        {
            std::cerr << "remaining unparsed: ";
            for (auto it=iter; it!=end; it++)
                std::cerr << showtoken(it->value());
            std::cerr << "\n";
        }
        if (r) return data;
    }
    catch (const qi::expectation_failure<iterator_type>& e)
    {
        std::cerr << "FIXME: expected " << e.what_ << ", got '";
        for (auto it=e.first; it!=e.last; it++)
            std::cerr << showtoken(it->value());
        std::cerr << "'" << std::endl;
    }
    return boost::none;
}

int main()
{
    for (std::string s : {
        "'aasdfa$gh' (1)",
        "'a\\' b,' (\n  -42 )",
        "'/this is my BOOLEAN     123label 12as' ( 123 )",
        "'a b',", // comma outside the string
        })
    {
        auto parsed = do_parse(s);

        std::cout << s << " -> " << std::boolalpha << parsed;

        if (parsed)
        {
            std::cout << " " << *parsed << "\n";
        } else
        {
            std::cout << "\n";
        }
    }
}

