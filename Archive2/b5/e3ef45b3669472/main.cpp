#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    std::string input("d:/std/prte/type.spr#12");
    std::string::const_iterator iter = input.begin(), end = input.end();
    std::pair<std::string, int> p;
    bool ok = qi::parse(iter, end,
            *qi::char_ >> '#' >> qi::int_,       // parser grammar 
            p
        );

    if (ok)
        std::cout << "Parse success\n";
    else
        std::cout << "Parse failed\n";


    if (iter != end)
        std::cout << "Remaining unparsed: '" << std::string(iter,end) << "'\n";
}
