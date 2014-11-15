#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;

template <typename It>
struct my_parser : qi::grammar<It> {
    my_parser() : my_parser::base_type(start) {
        using namespace qi;

        start                            = my_int_rule;
        my_int_rule                      = my_rule_with_inherited_attribute(_val);
        my_rule_with_inherited_attribute = int_ [ _r1 = _1 ]; // copied into the reference passed

        BOOST_SPIRIT_DEBUG_NODES((start)(my_rule_with_inherited_attribute)(my_int_rule))
    }

  private:
    qi::rule<It> start;
    qi::rule<It, int() > my_int_rule;
    qi::rule<It, void(int&) > my_rule_with_inherited_attribute;
};

int main()
{
    using It = std::string::const_iterator;
    my_parser<It> p;

    std::string const input = "123";

    bool ok = qi::parse(input.begin(), input.end(), p);

    std::cout << "Parse " << (ok? "success":"failed") << "\n";
}
