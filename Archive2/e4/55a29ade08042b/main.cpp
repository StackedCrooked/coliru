#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

struct identifier { std::list<char> name; };

namespace boost { namespace spirit { namespace traits {
    template<> struct is_container<identifier, void> : boost::mpl::true_ {};
    template<> struct container_value<identifier, void> { typedef char type; };
    template<> struct push_back_container<identifier, char, void> {
        static bool call(identifier& c, char val) {
            c.name.insert(c.name.end(), val); 
            return true;
        }
    };
}}}

int main()
{
    typedef std::string::const_iterator It;
    using namespace qi;

    rule<It, identifier()> gr_identifier = 
        as<std::vector<char>>() [ (alpha | '_') >> *(alnum | '_') ];

    std::string input = "foo goo(hoo)";

    It f(begin(input)), l(end(input));
    bool dummy = phrase_parse(f, l, gr_identifier, qi::space);

    return dummy? 0 : 255;
}

