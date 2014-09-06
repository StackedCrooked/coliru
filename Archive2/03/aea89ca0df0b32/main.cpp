#include <algorithm>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi      = boost::spirit::qi;
namespace phoenix = boost::phoenix;

struct Base {
    int x;
    double y;
};

BOOST_FUSION_ADAPT_STRUCT(Base, (int,x)(double,y))

struct Derived : Base { };

int main()
{
    typedef std::string::const_iterator It;
    qi::rule<It, Base(), qi::space_type> base_ = qi::int_ >> qi::double_;

    std::string const input = "1 3.14";
    auto f(input.begin()), l(input.end());

    Derived parse_result;
    bool ok = qi::phrase_parse(f, l, base_, qi::space, static_cast<Base&>(parse_result));
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
