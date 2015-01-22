#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

int main() {
    using It = std::string::const_iterator;
    qi::int_parser<uint8_t, 16, 2, 2> uint8_hex;

    std::string const src(
            "00112233445566778899aabbccddeeff;\n"
            "e98fb22cd1a3aa4a7fe1778a9e431211  ; 112134e9a8771ef7a4aa3a1dc22bf89e"            
        );
    auto f(src.begin()), l(src.end());

    using data_t = boost::array<uint8_t, 16>;

    static const qi::rule<It, data_t(), qi::locals<data_t::iterator> > rule = 
        qi::eps [ qi::_a = phx::begin(qi::_val) ]
        >> qi::repeat(16) [
                uint8_hex [ *qi::_a++ = qi::_1 ]
        ];

    std::vector<data_t> dst;
    bool r = qi::phrase_parse(f, l, rule % ';', qi::space, dst);

    if (r) {
        std::cout << "Parse succeeded\n";

        for(auto& a : dst) {
            for(unsigned i : a) std::cout << std::hex << std::showbase << i << " ";
            std::cout << "\n";
        }
    } else {
        std::cout << "Parse failed at '" << std::string(f,l) << "'\n";
    }
}
