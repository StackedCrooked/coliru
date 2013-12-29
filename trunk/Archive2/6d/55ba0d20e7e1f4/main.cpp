#include <assert.h>
#include <iostream>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

template <typename Skipper = qi::blank_type>
struct command_toten_parser : qi::grammar<const char *, std::string(), Skipper> {
    command_toten_parser() : command_toten_parser::base_type(r) {
        r = qi::lexeme [ +qi::graph ];
    }
    qi::rule<const char *, std::string(), Skipper> r;
};

int main(int argc, char *argv[]) {
    command_toten_parser<> p;
    std::string c, s(" asdf a1 a2 ");
    const char *b = &s[0];
    const char *e = b + s.size();

    assert(qi::phrase_parse(b, e, p, qi::blank, c));
    std::string rest(b, e);

    assert(c == std::string("asdf"));
    assert(rest == std::string("a1 a2 "));
}
