#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace phx   = boost::phoenix;

typedef std::vector<int> attr_t;

template <typename It, typename A>
    qi::rule<It, int()> kw(qi::rule<It, A()> const& p) { return qi::lazy(phx::cref(p)); }

template <typename It, typename P>
    qi::rule<It, int()> kw(P const& p) { return qi::lazy(phx::cref(p)); }

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, attr_t(), Skipper>
{
    parser() : parser::base_type(start)
    {
        using namespace qi;

        syms.add 
            ("one", 1)
            ("two", 2)
            ("three", 3);

        // wrap a rule
        symbol = syms;
        distinct_symbol = kw(symbol);

        // or just create one form the symbols parser:
        distinct_symbol = kw<It>(syms);


        start = *(distinct_symbol | qi::omit[ qi::lexeme[+qi::graph] ]);
    }

  private:
    qi::symbols<char, int> syms;
    qi::rule<It, int()> symbol, distinct_symbol;
    qi::rule<It, attr_t(), Skipper> start;
};

bool doParse(const std::string& input)
{
    typedef std::string::const_iterator It;
    auto f(begin(input)), l(end(input));

    parser<It, qi::space_type> p;
    attr_t data;

    try
    {
        bool ok = qi::phrase_parse(f,l,p,qi::space,data);
        if (ok)   
        {
            std::cout << "parse success\n";
            std::cout << "data: " << karma::format_delimited(karma::auto_, ' ', data) << "\n";
        }
        else      std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

        if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
        return ok;
    } catch(const qi::expectation_failure<It>& e)
    {
        std::string frag(e.first, e.last);
        std::cerr << e.what() << "'" << frag << "'\n";
    }

    return false;
}

int main()
{
    bool ok = doParse("one in three men are overweight");
    return ok? 0 : 255;
}
