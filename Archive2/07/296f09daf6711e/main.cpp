#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <iostream>
#include <vector>
#include <string>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace karma = boost::spirit::karma;
namespace phx = boost::phoenix;

struct foo {
    std::string f() const { return "bar"; }
};

int main()
{
    typedef std::back_insert_iterator<std::string> iterator;

    // this works:
    {
        std::string output;
        iterator it(output);

        std::vector<std::string> svec = { "foo", "bar", "baz" };
        karma::rule<iterator, std::vector<std::string>()> svec_rule = karma::string % ',';
        karma::generate(it, svec_rule, svec);
        std::cerr << output << '\n';
    }

    {
        std::string output;
        iterator it(output);

        std::vector<foo> vfoo(3);
        karma::rule<iterator, foo()> foo_rule = karma::string [ karma::_1 = phx::bind(&foo::f, karma::_val) ];
        //karma::rule<iterator, std::vector<foo> &()> vfoo_rule = karma::string  [ karma::_1 = phx::bind(&foo::f, karma::_val) ] % ',';
        karma::generate(it, foo_rule % ',', vfoo);
        std::cerr << output << '\n';
    }
}
