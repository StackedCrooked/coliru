#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

struct symbol { std::string repr; };
 //Change to `using symbol = std::string;` to make this work.
//using symbol = std::string;
BOOST_FUSION_ADAPT_STRUCT(symbol, (std::string, repr))

using namespace boost::spirit::qi;

template <typename Iterator>
struct test_grammar : grammar<Iterator, symbol(), ascii::space_type> {
    rule<Iterator, symbol(), ascii::space_type> start;

    test_grammar() : test_grammar::base_type{start} {
        start %= eps >> lexeme[+char_('a', 'z')];
    }
};

auto main() -> int {
    test_grammar<std::string::iterator> grammar{};
    auto input = std::string{"test"};
    auto output = symbol{};
    auto e = end(input);
    std::cout << phrase_parse(begin(input), e, grammar, ascii::space, output);
}