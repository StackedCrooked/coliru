#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/phoenix/function/adapt_function.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

void handle_label(std::string const& s) { std::cout << "Parsed label '" << s << ":'\n"; }
BOOST_PHOENIX_ADAPT_FUNCTION(void, handle_label_, handle_label, 1)

bool using_lexeme(std::string const& input)
{
    using namespace qi;
    static const rule<std::string::const_iterator, std::string()> 
        Identifier = alpha >> *(alnum | char_("_")),
        Label      = Identifier >> ':';

    auto f(input.begin()), l(input.end());
    return phrase_parse(f, l, Label [ handle_label_(_1) ], space);
}

int main()
{
    assert( using_lexeme("some_id:"));
    assert( using_lexeme("some_id: "));
    assert( using_lexeme(" some_id:"));
    assert(!using_lexeme("some_id :"));
}
