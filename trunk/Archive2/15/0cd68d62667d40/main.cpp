#include <vector>
#include <string>
#include <iostream>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace t {
    using std::vector;
    using std::string;

    struct Block {
        vector<string> value;
        Block(vector<string> v = {}) : value(std::move(v)) {}
    };
}

namespace boost { namespace spirit { namespace traits {
    //template<> struct is_container<t::Block, void> : mpl::false_ {};
} } }

//BOOST_FUSION_ADAPT_STRUCT(t::Block,(std::vector<std::string>,value))

namespace t {
    namespace qi = boost::spirit::qi;

    template <typename Iterator, typename Skipper=qi::space_type>
    struct G1 : qi::grammar<Iterator, Block(), Skipper> {

        template <typename T>
        using rule = qi::rule<Iterator, T, Skipper>;

        G1() : G1::base_type(start, "G1") {
            item  = +(qi::char_ - ';') >> ';';
            items = *item;
            start = '{' >> items >> '}';
        }

      private:
        rule<Block()> start;
        rule<std::string()> item;
        rule<std::vector<std::string>()> items;
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
