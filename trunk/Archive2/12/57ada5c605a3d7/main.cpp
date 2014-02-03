#include <boost/spirit/include/qi.hpp>

struct symbol 
{ 
    std::string repr; 

    symbol(std::string repr = std::string()) : repr(std::move(repr)) {}
};

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct test_grammar : qi::grammar<Iterator, symbol(), qi::ascii::space_type> {
    test_grammar() : test_grammar::base_type(start) {
        using namespace qi;

        start = as_string[ lexeme[ +char_("a-z") ] ];
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