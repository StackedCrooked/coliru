#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct unsigned_parser : qi::grammar<Iterator, uint64_t()> {

    unsigned_parser() : unsigned_parser::base_type(start) {
        using namespace qi;

        start = 
              eps [_val=0] >> +(char_("0-9a-fA-F") [ _val = _val*16 + _decode(_1) ] | '_')>>  char_("hHxX") /* hexadecimal with suffix */
            | eps [_val=0] >> +(char_("0-7")       [ _val = _val* 8 + _decode(_1) ] | '_')>>  char_("qQoO") /* octal       with suffix */
            | eps [_val=0] >> +(char_("01")        [ _val = _val* 2 + _decode(_1) ] | '_')>>  char_("bByY") /* binary      with suffix */
            | eps [_val=0] >> +(char_("0-9")       [ _val = _val*10 + _decode(_1) ] | '_')>> -char_("dDtT") /* decimal     with optional suffix */
            ;
    }
  private:
    struct decode {
        template <typename> struct result { typedef int type; };
        template <typename Ch> int operator()(Ch ch) const {
            if (ch>='0' && ch<='9') return ch - '0';
            if (ch>='a' && ch<='z') return ch - 'a' + 10;
            if (ch>='A' && ch<='Z') return ch - 'A' + 10;
            assert(false);
        }
    };
    boost::phoenix::function<decode> _decode;
    qi::rule<Iterator, uint64_t()> start;
};

int main() {
    typedef std::string::const_iterator It;
    unsigned_parser<It> up;

    for (std::string const test : {
            "123_456",
            "123456",
            "1_bh",
            "0_010Q",
            "1010_1010_0111_0111_b"
            })
    {
        It i = test.begin(), end = test.end();

        uint64_t val;
        bool rv = parse(i, end, up, val);

        std::cout << (rv?"Successful":"Failed") << " parse: '" << test << "' -> " << val << "\n";

        if (i != end)
            std::cout << " ** Remaining unparsed: '" << std::string(i,end) << "'\n";
    }
}
