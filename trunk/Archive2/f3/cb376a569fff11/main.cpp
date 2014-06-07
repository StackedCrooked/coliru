#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_DEBUG_PRINT_SOME 40
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    std::string input("d:/std/prte/type.spr#12");
    typedef std::string::const_iterator It;

    std::pair<std::string, int> p;

    qi::rule<It, std::string()> srule = *qi::char_;
    qi::rule<It, int()> irule         = qi::int_;
    BOOST_SPIRIT_DEBUG_NODES((srule)(irule))

    It iter = input.begin(), end = input.end();
    bool ok = qi::parse(iter, end,
            srule >> '#' >> irule,       // parser grammar 
            p
        );

    if (ok)
        std::cout << "Parse success\n";
    else
        std::cout << "Parse failed\n";


    if (iter != end)
        std::cout << "Remaining unparsed: '" << std::string(iter,end) << "'\n";
}
