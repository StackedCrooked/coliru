#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct unsigned_parser : qi::grammar<Iterator, uint64_t()> {

    unsigned_parser() : unsigned_parser::base_type(start) {
        using namespace qi;

        start = 
                (raw[+char_("_0-9a-fA-F")] >>  char_("hHxX")) [ _val = _evaluate(_1,_2) ] /* hexadecimal with suffix */
              | (raw[+char_("_0-7")]       >>  char_("qQoO")) [ _val = _evaluate(_1,_2) ] /* octal       with suffix */
              | (raw[+char_("_01")]        >>  char_("bByY")) [ _val = _evaluate(_1,_2) ] /* binary      with suffix */
              | (raw[+char_("_0-9")]       >> (char_("dDtT") | attr('T'))) 
                                                              [ _val = _evaluate(_1,_2) ] /* decimal     with optional suffix */
              ;
    }
  private:
    struct evaluate {
        template <typename, typename> struct result { typedef uint64_t type; };
        template <typename Raw, typename Ch> uint64_t operator()(Raw raw, Ch disciminator) const {
            std::string s(raw.begin(), raw.end());
            s.erase(std::remove(s.begin(), s.end(), '_'), s.end());
            char *f(&s[0]), *l(f+s.size());
            switch (disciminator) {
                case 'h': case 'H': case 'x': case 'X': return std::strtoul(f, &l, 16);
                case 'q': case 'Q': case 'o': case 'O': return std::strtoul(f, &l,  8);
                case 'b': case 'B': case 'y': case 'Y': return std::strtoul(f, &l,  2);
                case 'd': case 'D': case 't': case 'T': return std::strtoul(f, &l, 10);
                default: assert(false);
            };
        }
    };
    boost::phoenix::function<evaluate> _evaluate;
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
