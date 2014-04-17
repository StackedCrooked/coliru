#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi  = boost::spirit::qi;

struct header_t
{
    header_t(uint16_t i1=0, uint16_t i2=0, uint16_t i3=0, uint16_t i4=0) : int1(i1), int2(i2), int3(i3), int4(i4) { }

    static header_t make(uint16_t w1, uint16_t w2, uint16_t w3)
    {
#define BITS(n) ((1ul << (n)) - 1u)
        return header_t(
                (w1 & BITS(6u)),  // 6
                (w1 >> 6u),       // 10
                (w2 & BITS(14u)), // 14
                                  // 2+14
                ((w2 >> 14u) | ((w3 & BITS(14)) << 2) ));
    }
    
    uint16_t int1; // 6
    uint16_t int2; // 10
    uint16_t int3; // 14
    uint16_t int4; // 2+14
};

typedef const char* parse_iter_t;

int main()
{
    using qi::big_word;

    parse_iter_t iter = "\xff\x3e"
                        "\x44\x77"
                        "\x35\x19";
    //parse_iter_t iter = "\xff\xff"
                        //"\xff\xff"
                        //"\xff\xff";

    parse_iter_t iter_end = iter + std::strlen(iter);

    qi::rule<parse_iter_t, header_t()> header_rule;

    header_rule = (big_word >> big_word >> big_word)
                        [ qi::_val = boost::phoenix::bind(header_t::make, qi::_1, qi::_2, qi::_3) ];

    header_t result;
    bool ok = qi::parse(iter, iter_end, header_rule, result);

    if (ok)
    {
        std::cout << "int1: " << std::dec << result.int1 << " " << std::hex << std::showbase << result.int1 << "\n";
        std::cout << "int2: " << std::dec << result.int2 << " " << std::hex << std::showbase << result.int2 << "\n";
        std::cout << "int3: " << std::dec << result.int3 << " " << std::hex << std::showbase << result.int3 << "\n";
        std::cout << "int4: " << std::dec << result.int4 << " " << std::hex << std::showbase << result.int4 << "\n";
    }

    assert(ok);
}
