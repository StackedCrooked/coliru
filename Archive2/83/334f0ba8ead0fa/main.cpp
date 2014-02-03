#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>

struct symbol 
{ 
    std::string repr; 
};

BOOST_FUSION_ADAPT_STRUCT(symbol, (std::string, repr))

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct test_grammar : qi::grammar<Iterator, symbol(), qi::ascii::space_type> {
    test_grammar() : test_grammar::base_type{start} {
        start = qi::eps >> qi::lexeme[+qi::char_("a-z")];
    }

    qi::rule<Iterator, symbol(), qi::ascii::space_type> start;
};

#include <iostream>

auto main() -> int {
    test_grammar<std::string::iterator> grammar{};
    auto input = std::string{"test"};
    auto output = symbol{};
    auto e = end(input);
    if (qi::phrase_parse(begin(input), e, grammar, qi::ascii::space, output))
        std::cout << output.repr;
}
