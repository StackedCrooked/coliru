#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

template <typename Int>
void do_test()
{
    for (Int const testcase : { 
            std::numeric_limits<Int>::min(),
            Int(),
            std::numeric_limits<Int>::max()
            })
    {
        auto const input = std::to_string(testcase);

        bool negative = false;
        Int parsed = 0;

        using namespace qi;
        auto f(input.begin()), l(input.end()); 

        bool ok = parse(f, l,
                (matches['-']  | -lit('+') >> attr(false)) [ phx::ref(negative) = _1 ] >> // sign
                eps    [ _val = 0 ] >>
                +digit [ _val *= 10, _val += (_1 - '0') ],
                parsed);

        if (!ok || f!=l)
            throw std::runtime_error("parse error");

        if (negative)
            parsed = -parsed;

        std::cout << std::boolalpha << (testcase==parsed) << "\t" << std::to_string(testcase) << " -> " << std::to_string(parsed) << "\n";
    }
}



int main()
{
    do_test<int16_t>();
    do_test<uint16_t>();
    do_test<int32_t>();
    do_test<uint32_t>();
    do_test<int64_t>();
    do_test<uint64_t>();
    do_test<int8_t>();
    do_test<uint8_t>();
    do_test<intmax_t>();
    do_test<uintmax_t>();
}
