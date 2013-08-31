#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace phx = boost::phoenix;

int main()
{
    typedef std::string::const_iterator It;
    const std::string input = "[w1/[w2/w3]2/w4]3";

    std::vector<std::string> v;
    It first(input.begin()), last(input.end());

    using namespace boost::spirit::qi;

    rule<It, std::string(bool in_group)> raw;
    rule<It, std::vector<std::string>(bool in_group), space_type> 
        group, 
        delimited;

    _r1_type in_group; // friendly alias for the inherited attribute

    raw       = eps(in_group) >> +~char_("/]") 
              | +~char_("/");

    delimited = (group(in_group)|raw(in_group)) % '/';

    group     = ('[' >> delimited(in_group=true) >> ']' >> int_) 
        [ phx::while_(_2--) 
            [ phx::insert(_val, phx::end(_val), phx::begin(_1), phx::end(_1)) ]
        ];

    BOOST_SPIRIT_DEBUG_NODES((raw)(delimited)(group));

    bool r = phrase_parse(first, last, 
            delimited(false),
            space,v);

    if (r)
        std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
