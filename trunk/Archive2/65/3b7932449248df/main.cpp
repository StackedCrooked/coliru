#include <boost/multiprecision/cpp_int.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi  = boost::spirit::qi;

int main() {
    using boost::multiprecision::uint128_t;
    using It = std::string::const_iterator;
    qi::int_parser<uint128_t, 16, 16, 16> uint128_hex;

    std::string const src("00112233445566778899aabbccddeeff");
    auto f(src.begin()), l(src.end());

    uint128_t parsed;
    bool r = qi::parse(f, l, uint128_hex, parsed);

    if (r) std::cout << "Parse succeeded: " << std::hex << std::showbase << parsed << "\n";
    else   std::cout << "Parse failed at '" << std::string(f,l) << "'\n";

}
