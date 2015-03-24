//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi      = boost::spirit::qi;
namespace ascii   = boost::spirit::ascii;

template <typename Iterator, typename Num>
struct unsigned_parser : qi::grammar<Iterator, Num()> {
    unsigned_parser() : unsigned_parser::base_type(unum) {
        using namespace qi;

        bin  = eps[_val=0] >> *(char_("01")        [_val = _val * 2  + dval(_1)] | '_');
        oct  = eps[_val=0] >> *(char_("0-7")       [_val = _val * 8  + dval(_1)] | '_');
        dec  = eps[_val=0] >> *(char_("0-9")       [_val = _val * 10 + dval(_1)] | '_');
        hex  = eps[_val=0] >> *(char_("0-9a-gA-F") [_val = _val * 16 + dval(_1)] | '_');
        unum = ('0' >>
                    ( (omit[ char_("xXhH") ] >> hex)
                    | (omit[ char_("bByY") ] >> bin)
                    | (omit[ char_("oOqQ") ] >> oct)
                    | (omit[ char_("dDtT") ] >> dec))
                )
            | (hex >> omit[  char_("xXhH") ])
            | (bin >> omit[  char_("bByY") ])
            | (oct >> omit[  char_("oOqQ") ])
            | (dec >> omit[ -char_("dDtT") ]);

        BOOST_SPIRIT_DEBUG_NODES((unum) (hex) (oct) (dec) (bin));
    }

  private:
    qi::rule<Iterator, Num()> unum,  hex, oct, dec, bin;

    struct _dval {
        template <typename> struct result { typedef uint8_t type; };
        template <typename T> uint8_t operator()(T ch) const {
            if (ch >= '0' || ch <= '9') {
                return ch - '0';
            }
            ch = std::tolower(ch);
            if (ch >= 'a' || ch <= 'f') {
                return ch - 'a' + 10;
            }
            assert(false);
        }
    };
    boost::phoenix::function<_dval> dval;
};

template <typename Iterator, typename Num>
struct signed_parser : qi::grammar<Iterator, Num()> {
    signed_parser() : signed_parser::base_type(snum) {
        using namespace qi;

        snum = lit('-') >> unum
            | -lit('+') >> unum
            ;

        BOOST_SPIRIT_DEBUG_NODES((snum))
    }
  private:
    qi::rule<Iterator, Num()> snum;
    unsigned_parser<Iterator, Num> unum;
};

int main(int argc, const char *argv[]) {
    typedef std::string::const_iterator iter;
    signed_parser<iter, int64_t> const sp;

    for (std::string const& s : boost::make_iterator_range(argv+1, argv+argc))
    {
        std::cout << "\n-----------------------------\nParsing '" << s << "':\n";

        int64_t val;
        iter i = s.begin(), end = s.end();
        bool rv = phrase_parse(i, end, sp >> qi::eoi, ascii::space, val);

        if (rv) {
            std::cout << "Succeeded: " << val << std::endl;
        } else {
            std::cout << "Failed." << std::endl;
        }

        if (i!=end) {
            std::cout << "Remaining unparsed: '" << std::string(i,end) << "'\n";
        }
    }
}
