#define FUSION_MAX_VECTOR_SIZE 20
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

int main()
{
    qi::int_parser<uint8_t, 16, 2, 2> uint8_hex;

    std::string const src("00112233445566778899aabbccddeeff");
    auto f(src.begin()), l(src.end());

    boost::fusion::vector<uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t> dst {};
    bool r = qi::parse(f, l,
            uint8_hex >> uint8_hex >> uint8_hex >> uint8_hex >>
            uint8_hex >> uint8_hex >> uint8_hex >> uint8_hex >>
            uint8_hex >> uint8_hex >> uint8_hex >> uint8_hex >>
            uint8_hex >> uint8_hex >> uint8_hex >> uint8_hex
            , dst
            );

    if (r) {
        std::cout << "Parse succeeded\n";

        using phx::arg_names::arg1;
        boost::fusion::for_each(dst, phx::ref(std::cout) << std::hex << std::showbase << phx::static_cast_<int>(arg1) << " ");
    } else
    {
        std::cout << "Parse failed at '" << std::string(f,l) << "'\n";
    }
}
