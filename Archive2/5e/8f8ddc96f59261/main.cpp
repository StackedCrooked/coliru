// #define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>

namespace qi    = boost::spirit::qi;

template <typename It>
    struct parser : qi::grammar<It, std::string()>
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
    qi::rule<It, std::string()> P, S;
    qi::rule<It> V;
};

bool doParse(const std::string& input)
{
    typedef std::string::const_iterator It;
    auto f(begin(input)), l(end(input));

    parser<It> p;
    std::string data;

    bool ok = qi::parse(f,l,p,data);
    if (ok)   
    {
        std::cout << "parse success\ndata: " << data << "\n";
    }
    else std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

    if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
    return ok;
}

int main()
{
    bool ok = doParse("@anything but &at; followed of the string .PV@");
    return ok? 0 : 255;
}
