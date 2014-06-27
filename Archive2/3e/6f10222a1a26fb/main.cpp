#include <vector>
#include <string>
#include <iostream>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace t {
    using std::vector;
    using std::string;
    namespace qi = boost::spirit::qi;

    struct Block {
        vector<string> value;
    };
}

BOOST_FUSION_ADAPT_STRUCT(t::Block,(std::vector<std::string>,value))

namespace t {

    template <typename Iterator, typename Skipper=qi::space_type>
    struct G1 : qi::grammar<Iterator, Block(), Skipper> {

        template <typename T>
        using rule = qi::rule<Iterator, T, Skipper>;

        rule<Block()> start;
        G1() : G1::base_type(start, "G1") {
            start = 
                qi::lit('{')
                >> *qi::as_string [ +(qi::char_ - ';') >> ';' ]
                >> '}'
            ;
        }
    };

    Block parse(string const input) {
        G1<string::const_iterator> g;
        Block result;
        phrase_parse(begin(input), end(input), g, qi::standard::space, result);
        return result;
    }
}

int main() {
    using namespace std;
    auto r = t::parse("{abc;def;}");
    for (auto& s : r.value) {
        cout << s << endl;
    }
}
