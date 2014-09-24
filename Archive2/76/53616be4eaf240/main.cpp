#include <stdexcept>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace /*parser*/
{
    struct Day {
        Day(int i=1) : v_(i) { 
            if (i<1 || i>31) throw std::range_error("Day out of range");
        }

        operator int() const {
            return v_;
        }

      private:
        uint8_t v_;
    };

    namespace qi = boost::spirit::qi;

    template <typename It, typename Skipper = qi::unused_type>
        struct grammar : qi::grammar<It, Day(), Skipper>
    {
        grammar() : grammar::base_type(start_)
        {
            using namespace qi;
            start_ = uint_parser<uint8_t, 10, 1, 2>() [ _pass = (_1>=1 && _1<=31) ];
        }
      private:
        qi::rule<It, Day(), Skipper> start_;
    };

} /*parser*/

int main()
{
    typedef std::string::const_iterator It;
    grammar<It> g;
    
    for (int i = -10; i < 40; ++i)
    {
        auto const s = std::to_string(i);
        auto f(s.begin()), l(s.end());

        Day parsed;
        if (qi::parse(f,l,g,parsed))
            std::cout << "Parsed ok: '" << s << "' -> " << parsed << "\n";
        else
            std::cout << "Parse failed: '" << s << "'\n";

        if (f!=l)
            std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
    }
}
