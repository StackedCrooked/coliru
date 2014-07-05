using max_align_t=double;

#define BOOST_RESULT_OF_USE_DECLTYPE
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <vector>
#include <string>
#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace t {
    using std::vector;
    using std::string;
    namespace qi = boost::spirit::qi;
    namespace phx = boost::phoenix;

    template <typename Iterator, typename Skipper=qi::space_type>
    struct G1 : qi::grammar<Iterator, string(), Skipper> {

        template <typename T>
        using rule = qi::rule<Iterator, T, Skipper>;

        qi::rule<Iterator, string(), qi::locals<char>> quoted_string;
        rule<string()> start;

        G1() : G1::base_type(start, "G1") {
            {
                using qi::_1;
                using qi::_a;

                using attr_signature = vector<char>;
                auto handler = [](attr_signature const& elements) -> string {
                    string output;
                    for(auto& e : elements) {
                        output += e;
                    }
                    return output;
                };
                quoted_string = (qi::omit[qi::char_("'\"")[_a = _1]]
                    >> +(qi::char_ - qi::char_(_a))
                    >> qi::lit(_a))[qi::_val += phx::bind(handler, _1)];
            }
            start = qi::string("foo") >> -(qi::string("=") >> quoted_string);
        }
    };

    string parse(string const input) {
        G1<string::const_iterator> g;
        string result;
        phrase_parse(begin(input), end(input), g, qi::standard::space, result);
        return result;
    }
};

int main() {
    using namespace std;
    auto r = t::parse("foo='hello'");
    cout << r << endl;
}
