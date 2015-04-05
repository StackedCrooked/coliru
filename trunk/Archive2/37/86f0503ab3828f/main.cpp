#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

template <typename It, typename Skipper>
struct max_parser : qi::grammar<It, std::string(), Skipper> {
    max_parser() : max_parser::base_type(start) {
        using namespace qi;
        using phx::if_;

#if 1
        word  = lexeme [ +alpha ];
        start = *word [ if_(_1>_val) [_val=_1], _pass = true ];
#else
        start = *as_string[lexeme[+alpha]] [ if_(_1>_val) [_val=_1], _pass = true ];
#endif
    }

  private:
    qi::rule<It, std::string(), Skipper> start, word;
};


int main() {

    std::string const input("beauty shall be in ze eye of the beholder");
    using It = std::string::const_iterator;
    max_parser<It, qi::space_type> parser;

    std::string data;
    It it = input.begin(), end = input.end();
    bool ok = qi::phrase_parse(it, end, parser, qi::space, data);

    if (ok) {
        std::cout << "Parse success: " << data << "\n";
    } else {
        std::cout << "Parse failed\n";
    }

    if (it != end)
        std::cout << "Remaining unparsed: '" << std::string(it,end) << "'\n";
}

