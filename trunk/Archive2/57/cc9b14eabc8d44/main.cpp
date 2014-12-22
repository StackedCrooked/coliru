// #define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

using data = std::vector<std::vector<unsigned> >;

template <typename It, typename Skipper = qi::space_type> 
struct grammar : qi::grammar<It, data(), Skipper> {
    grammar() : grammar::base_type(start) {
        using namespace qi;

        start = *seq_;

        seq_  = -item_('7') >> -item_('8') >> -item_('9') >> -item_('0')
              >> eps(phx::size(_val) > 0)
              ;
        
        item_ = omit[char_(_r1)] >> uint_;

        BOOST_SPIRIT_DEBUG_NODES((start)(item_)(seq_))
    }

  private:
    qi::rule<It, unsigned(char), Skipper> item_;
    qi::rule<It, std::vector<unsigned>(), Skipper> seq_;
    qi::rule<It, data(), Skipper> start;
};

int main() { 

    for (std::string const input : {
            "71122 85451 75415 01102 75555 82133 91341 02134"
            })
    {
        using It = std::string::const_iterator;
        grammar<It> p;
        auto f(input.begin()), l(input.end());

        data parsed;
        bool ok = qi::phrase_parse(f,l,p,qi::space,parsed);

        std::cout << "Parsing: " << input << "\n";
        if (ok) {
            std::cout << "Parsed: " << parsed.size() << " sequences\n";
            for(auto& seq : parsed)
                std::copy(seq.begin(), seq.end(), std::ostream_iterator<unsigned>(std::cout << "\nseq:\t", " "));
            std::cout << "\n";
        } else {
            std::cout << "Parsed failed\n";
        }

        if (f!=l)
            std::cout << "Remaining unparsed input: '" << std::string(f,l) << "'\n";
    }
}
