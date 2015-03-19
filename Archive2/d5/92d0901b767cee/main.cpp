#define ALLOW_SO_UNDERSCORE_HACK
#include "numeric_utils.hpp"
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct unsigned_parser : qi::grammar<Iterator, uint64_t()> {

    unsigned_parser() : unsigned_parser::base_type(start) {
        using namespace qi;
        uint_parser<uint64_t, 10> dec_parser;
        uint_parser<uint64_t, 16> hex_parser;
        uint_parser<uint64_t, 8> oct_parser;
        uint_parser<uint64_t, 2> bin_parser;

        start = eps(false)
            | (hex_parser >> omit[ char_("hHxX")]) /* hexadecimal with suffix */
            | (oct_parser >> omit[ char_("qQoO")]) /* octal with suffix */
            | (bin_parser >> omit[ char_("bByY")]) /* binary with suffix */
            | (dec_parser >> omit[-char_("dDtT")]) /* decimal with optional suffix */
            ;
    }

    qi::rule<Iterator, uint64_t()> start;
};

int main(int argv, const char *argc[]) {
    typedef std::string::const_iterator iter;
    unsigned_parser<iter> up;

    for (auto const& test : std::vector<std::string>(argc+1, argc+argv)) {
        iter i = test.begin(), end = test.end();

        uint64_t val;
        bool rv = parse(i, end, up, val);

        std::cout << (rv?"Successful":"Failed") << " parse: '" << test << "' -> " << val << "\n";

        if (i != end)
            std::cout << " ** Remaining unparsed: '" << std::string(i,end) << "'\n";
    }
}
