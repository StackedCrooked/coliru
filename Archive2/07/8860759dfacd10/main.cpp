#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <algorithm>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

struct Base {
    int x;
    double y;
};

BOOST_FUSION_ADAPT_STRUCT(Base, (int,x)(double,y))

struct Derived : Base { };

template <typename It, typename Skipper = qi::space_type>
struct derived_grammar : qi::grammar<It, Derived(), Skipper>
{
    derived_grammar() : derived_grammar::base_type(start) {
        base_ = qi::int_ >> qi::double_;
        glue_ = base_ [ qi::_r1 = qi::_1 ];
        start = "derived:" >> glue_(qi::_val); // passing the exposed attribute for the `Base&` reference
    }
  private:
    qi::rule<It, Derived(),   Skipper> start;
    qi::rule<It, void(Base&), Skipper> glue_;
    qi::rule<It, Base(),      Skipper> base_; // could be a grammar instead of a rule
};

int main()
{
    typedef std::string::const_iterator It;
    derived_grammar<It> g;

    std::string const input = "derived:1 3.14";
    auto f(input.begin()), l(input.end());

    Derived parse_result;
    bool ok = qi::phrase_parse(f, l, g, qi::space, parse_result);
    if (ok)
    {
        std::cout << "Parsed: " << parse_result.x << " " << parse_result.y << "\n";
    } else
    {
        std::cout << "Parse failed\n";
    }

    if (f != l)
    {
        std::cout << "Input remaining: '" << std::string(f,l) << "'\n";
    }
}
