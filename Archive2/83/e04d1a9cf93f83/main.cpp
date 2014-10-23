#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

struct Node {
    std::string text;
};

BOOST_FUSION_ADAPT_STRUCT(Node, (std::string, text))

template <typename Iterator> struct My_parser : qi::grammar<Iterator, Node()> {
    My_parser() : My_parser::base_type(node_line) {
        name %= +ascii::char_;
        node = qi::eps >> name;

        node_line = "  * " >> node [qi::_val=qi::_1];
    }

    qi::rule<Iterator, std::string()> name;
    qi::rule<Iterator, Node()> node_line;
    qi::rule<Iterator, Node()> node;
};

int main() {
    const std::string input("  * Some text");
    Node parsed;
    My_parser<std::string::const_iterator> my_parser;

    bool r = parse(input.begin(), input.end(), my_parser, parsed);

    if (r)
        std::cout << "Match: " << parsed.text << std::endl;
    else
        std::cout << "No match" << std::endl;

    return 0;
}
