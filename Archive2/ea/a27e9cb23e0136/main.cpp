#include "boost/spirit/include/qi.hpp"
#include "boost/spirit/include/phoenix.hpp"
#include "boost/fusion/adapted/struct.hpp"

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;
typedef std::string::const_iterator It;

struct S
{
    int         field1;
    std::string field2;
    int         target_field;
    bool        field3;
};

BOOST_FUSION_ADAPT_STRUCT(S, (int, field1)(std::string, field2)(int, target_field)(bool, field3))

int main()
{
    const std::string input("42");
    It f(begin(input)), l(end(input));

    S instance;

    using namespace qi;
    rule<It, S()> p = int_ [ phx::at_c<2>(_val) = _1 ];

    if (parse(f, l, p, instance))
        std::cout << "Parsed: " << instance.target_field;
}
