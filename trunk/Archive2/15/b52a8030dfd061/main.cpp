//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_DEBUG_OUT std::cerr

#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_symbols.hpp>
#include <iostream>
#include <vector>

struct Thing
{
    std::string one;
    std::string two;
};

BOOST_FUSION_ADAPT_STRUCT(
    Thing,
    (std::string, one)
    (std::string, two)
)

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct parse_things : qi::grammar<Iterator, Thing(), ascii::space_type>
{
    parse_things() : parse_things::base_type(keyword)
    {
        keywords.add
            ("One", Thing{"ThingOne","ThingTwo"})
            ("Two", Thing{"ThingTwo","ThingOne"});

        keyword %= keywords;
        BOOST_SPIRIT_DEBUG_NODE(keyword);
    }

    qi::symbols<char, Thing> keywords;
    qi::rule<Iterator, Thing(), ascii::space_type> keyword;
};

int main()
{
    const parse_things<std::string::const_iterator> parser;

    for (std::string const s : { "One", "Two", "Three" })
    {
        auto f = begin(s), l = end(s);
        Thing data;

        bool ok = qi::phrase_parse(f,l,parser,ascii::space,data);

        std::cout << s << ": " << std::boolalpha << ok << ", " << boost::fusion::as_vector(data) << '\n';
        if (f != l)
            std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
    }
}
