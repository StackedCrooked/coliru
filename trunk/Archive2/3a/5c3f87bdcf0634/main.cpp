#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct unsigned_parser : qi::grammar<Iterator, uint64_t()> {

    unsigned_parser() : unsigned_parser::base_type(start) {
        using namespace qi;

        start = 
                (raw[+char_("_0-9a-fA-F")] >>  char_("hHxX")) [ _val = _strtoul(_1,16) ] /* hexadecimal with suffix */
              | (raw[+char_("_0-7")]       >>  char_("qQoO")) [ _val = _strtoul(_1, 8) ] /* octal       with suffix */
              | (raw[+char_("_01")]        >>  char_("bByY")) [ _val = _strtoul(_1, 2) ] /* binary      with suffix */
              | (raw[+char_("_0-9")]       >> -char_("dDtT")) [ _val = _strtoul(_1,10) ] /* decimal     with optional suffix */
              ;
    }
  private:
    struct strtoul_f {
        template <typename, typename> struct result { typedef uint64_t type; };
        template <typename Raw, typename Int> uint64_t operator()(Raw raw, Int base) const {
            std::string s(raw.begin(), raw.end());
            s.erase(std::remove(s.begin(), s.end(), '_'), s.end());
            char *f(&s[0]), *l(f+s.size());
            return std::strtoul(f, &l, base);
        }
    };
    boost::phoenix::function<strtoul_f> _strtoul;
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
