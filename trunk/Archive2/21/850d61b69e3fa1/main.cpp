// #define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_confix.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

typedef std::string attr_t;

template <typename It>
    struct parser : qi::grammar<It, attr_t()>
{
    parser() : parser::base_type(P)
    {
        using namespace qi;

        P = S >> V;
        S = '@' >> +(char_ - '@' - V);
        V = ".PV@";
        BOOST_SPIRIT_DEBUG_NODES((P)(S)(V));
    }

  private:
    qi::rule<It, attr_t()> P, S;
    qi::rule<It> V;
};

bool doParse(const std::string& input)
{
    typedef std::string::const_iterator It;
    auto f(begin(input)), l(end(input));

    parser<It> p;
    attr_t data;

    try
    {
        bool ok = qi::parse(f,l,p,data);
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
    bool ok = doParse("@anything but &at; followed of the string .PV@");
    return ok? 0 : 255;
}
