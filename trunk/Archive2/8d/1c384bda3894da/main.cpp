#define BOOST_SPIRIT_DEBUG
#include "boost/spirit/include/qi.hpp" 
#include "boost/spirit/include/karma.hpp" 
#include "boost/fusion/include/std_pair.hpp" 
#include <fstream> 
#include <map> 

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;

template <typename It, typename Skipper, typename Data>
struct kvp_grammar : qi::grammar<It, Data(), Skipper> {
    kvp_grammar() : kvp_grammar::base_type(start) {
        using namespace qi;

        value        = raw [*print];
        quoted_value = '"' >> *~char_('"') >> '"';
        key          = raw [ alpha >> *(alnum | '_') ];

        kvp          = key >> '=' >> (quoted_value | value);
        start        = -(kvp % +eol);

        BOOST_SPIRIT_DEBUG_NODES((value)(quoted_value)(key)(kvp));
    }
  private:
    using Pair = std::pair<std::string, std::string>;
    qi::rule<It, std::string(), Skipper> value;
    qi::rule<It, Pair(),        Skipper> kvp;
    qi::rule<It, Data(),        Skipper> start;
    // lexeme:
    qi::rule<It, std::string()> quoted_value, key;
};

template <typename Map>
bool parse_vars(std::istream& is, Map& data) {
    using It = boost::spirit::istream_iterator;
    using Skipper = qi::rule<It>;

    kvp_grammar<It, Skipper, Map> grammar;
    It f(is >> std::noskipws), l;

    Skipper skipper = ('#' >> *(qi::char_-qi::eol)) | qi::blank;
    return qi::phrase_parse(f, l, grammar, skipper, data); 
}

int main() { 
    std::ifstream ifs("input.txt"); 

    std::map<std::string, std::string> vars; 

    if (parse_vars(ifs, vars)) {
        std::cout << "vars[" << vars.size() << "]:" << std::endl; 
        std::cout << karma::format(*(karma::string << " -> " << karma::string << karma::eol), vars); 
    }
}
