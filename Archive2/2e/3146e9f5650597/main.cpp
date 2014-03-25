#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/lexical_cast.hpp>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

namespace boost { namespace spirit { namespace traits { 

    template <typename Int>
        struct assign_to_attribute_from_value<
            Int, 
            std::string,
            typename std::enable_if<std::is_integral<Int>::value, void>::type // Enabler
            >
        {
            static void call(std::string const& val, Int& attr) {
                //std::cout << __PRETTY_FUNCTION__ << "('" << val << "')\n";
                attr = boost::lexical_cast<Int>(val);
            }
        };

    // boost lexical_cast does not usefully support `char` types as integrals... (SIC)
    template <>
        struct assign_to_attribute_from_value<signed char, std::string> {
            static void call(std::string const& val, signed char& attr) {
                int tmp;
                assign_to_attribute_from_value<int, std::string>::call(val, tmp);
                attr = static_cast<signed char>(tmp);
            }
        };

    template <>
        struct assign_to_attribute_from_value<unsigned char, std::string> {
            static void call(std::string const& val, unsigned char& attr) {
                unsigned int tmp;
                assign_to_attribute_from_value<unsigned int, std::string>::call(val, tmp);
                attr = static_cast<unsigned char>(tmp);
            }
        };

} } }

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

        using namespace qi;
        auto f(input.begin()), l(input.end()); 

        Int parsed = 0;
        bool ok = parse(f, l, as_string [ -char_("-+") >> +digit ], parsed);

        if (!ok || f!=l)
            throw std::runtime_error("parse error");

        std::cout << std::boolalpha << (testcase==parsed) << "\t" << std::to_string(testcase) << " -> " << std::to_string(parsed) << "\n";
    }
}

int main()
{
    do_test<int8_t>();
    do_test<uint8_t>();
    do_test<int16_t>();
    do_test<uint16_t>();
    do_test<int32_t>();
    do_test<uint32_t>();
    do_test<int64_t>();
    do_test<uint64_t>();
    do_test<intmax_t>();
    do_test<uintmax_t>();
}
