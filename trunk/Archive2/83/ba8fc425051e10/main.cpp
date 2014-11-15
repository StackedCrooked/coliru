#define BOOST_SPIRIT_DEBUG
#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;

template <typename It>
struct my_parser : qi::grammar<It> {
    my_parser() : my_parser::base_type(start) {
        using namespace qi;

        my_rule_with_a_local = my_int_rule [ _a = _1 ]; // copied into the reference passed
        my_int_rule          = int_; 

        start = my_rule_with_a_local;
        BOOST_SPIRIT_DEBUG_NODES((start)(my_rule_with_a_local)(my_int_rule))
    }

  private:
    qi::rule<It> start;
    qi::rule<It, int() > my_int_rule;
    qi::rule<It, qi::locals<int> > my_rule_with_a_local;
};

int main()
{
    using It = std::string::const_iterator;
    my_parser<It> p;

    std::string const input = "123";

    bool ok = qi::parse(input.begin(), input.end(), p);

    std::cout << "Parse " << (ok? "success":"failed") << "\n";
}
