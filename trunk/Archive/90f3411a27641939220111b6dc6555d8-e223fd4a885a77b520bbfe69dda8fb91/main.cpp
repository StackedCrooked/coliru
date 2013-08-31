#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace phx = boost::phoenix;

int main()
{
    const std::string input = "w1/[w2/[w3]3]2/w4";

    std::vector<std::string> v;
    auto first(begin(input)), last(end(input));

    using namespace boost::spirit::qi;

    rule<std::string::const_iterator, std::string(bool in_group)> raw;
    rule<std::string::const_iterator, std::vector<std::string>(bool in_group), space_type> 
        group, 
        delimited;

    _r1_type in_group; // friendly alias for the inherited attribute

    raw       = eps(in_group) >> +~char_("/]") | +~char_("/");
    delimited = (group(in_group)|raw(in_group)) % '/';
    group     = ('[' >> delimited(in_group=true) >> ']' >> int_) [
        phx::while_(_2--) [
           phx::insert(_val, phx::end(_val), phx::begin(_1), phx::end(_1)) 
        ]
      ];

    bool r = phrase_parse(first, last, 
            delimited(false),
            space,v);

    if (r) for(auto& el : v)
            std::cout << el << "\n";
}
