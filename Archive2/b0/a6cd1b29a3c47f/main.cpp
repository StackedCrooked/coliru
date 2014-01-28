// #define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>
#include <stdexcept>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

using s_expr = boost::make_recursive_variant<std::string, std::vector<boost::recursive_variant_> >::type;
using s_list = std::vector<s_expr>;

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, s_expr(), Skipper>
{
    parser() : parser::base_type(expr)
    {
        using namespace qi;

        value = lexeme [ +(graph - '(' - ')') ];
        list  = '(' >> *expr >> ')';
        expr  = list | value;

        BOOST_SPIRIT_DEBUG_NODES((expr)(value)(list));
    }

  private:
    qi::rule<It, s_expr(),      Skipper> expr;
    qi::rule<It, std::string(), Skipper> value;
    qi::rule<It, s_list(),      Skipper> list;
};

s_expr parse_s_expr(const std::string& input)
{
    typedef std::string::const_iterator It;

    static const parser<It, qi::space_type> p;

    It f(begin(input)), l(end(input));
    s_expr data;

    if (!qi::phrase_parse(f,l,p,qi::space,data))
        throw std::runtime_error("parse failed: '" + std::string(f,l) + "'");

    return data;
}

namespace std { // a hack for easy debug printing
    static inline std::ostream& operator<<(std::ostream& os, s_list const& l) {
        os << "( "; std::copy(l.begin(), l.end(), std::ostream_iterator<s_expr>(os, " "));
        return os << ")";
    }

}

int main()
{
    s_expr parsed = parse_s_expr(
            "(TOP\n"
            "  (S\n"
            "    (NP (DT This))\n"
            "    (VP\n"
            "      (VBZ uploads)\n"
            "      (NP (NNS files))\n"
            "      (PP (TO to) (NP (DT a) (JJ remote) (NN machine))))\n"
            "    (. .)"
            ")"
            ")");

    std::cout << "parsed: " << parsed           << "\n";

    // conversely, just build one:
    const s_expr in_code(s_list { 
        "TOP",
        s_list { "S",
            s_list { "NP", s_list { "DT", "This", } },
            s_list { "VP",
                s_list { "VBZ", "uploads" },
                    s_list { "NP", s_list { "NNS", "files" } },
                    s_list { "PP", s_list { "TO", "to" }, s_list { "NP", s_list { "DT", "a" }, s_list { "JJ", "remote" }, s_list { "NN", "machine" } } } },
                s_list { ".", "." }
        }
    });

    // both AST trees are exactly equivalent:
    assert(in_code == parsed);
}
