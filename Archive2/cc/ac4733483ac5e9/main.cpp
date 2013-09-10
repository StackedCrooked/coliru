#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, unsigned(), Skipper>
{
    parser() : parser::base_type(array_typeexp)
    {
        using namespace qi;
        // using phx::bind; using phx::ref; using phx::val;

        empty_brackets    = lit('(') >> lit(')');
        n_empty_brackets  = eps [ _val = 0 ] >> +empty_brackets [ ++_val ];

        array_typeexp     = primitive_typeexp >> n_empty_brackets;

        // TODO
        primitive_typeexp = eps;

        BOOST_SPIRIT_DEBUG_NODES((array_typeexp)(n_empty_brackets)(empty_brackets)(primitive_typeexp));
    }

  private:
    qi::rule<It, unsigned(), Skipper> array_typeexp, n_empty_brackets;
    qi::rule<It, Skipper> empty_brackets, primitive_typeexp;
};

bool doParse(const std::string& input)
{
    typedef std::string::const_iterator It;
    auto f(begin(input)), l(end(input));

    parser<It, qi::space_type> p;
    unsigned data;

    try
    {
        bool ok = qi::phrase_parse(f,l,p,qi::space,data);
        if (ok)   
        {
            std::cout << "parse success\n";
            std::cout << "data: " << data << "\n";
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
    doParse("() () (     ) ()");
    doParse("()");
}
