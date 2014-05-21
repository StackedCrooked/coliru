#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>

using It         = std::string::iterator;
using tokref     = boost::iterator_range<It>;
using swappables = std::pair<tokref, tokref>;

namespace qi = boost::spirit::qi;

int main()
{
    std::string input = "read A var := 5";

    It first(input.begin()), last(input.end());

    using boost::phoenix::construct;
    using boost::phoenix::push_back;
    using namespace qi;

    qi::rule<It, tokref()>                     token_ = qi::raw[+qi::graph];
    qi::rule<It, swappables(), qi::space_type> swap_  = (token_ >> token_) [ _val = construct<swappables>(_1, _2) ];

    std::vector<swappables> to_swap;

    std::cout << input << "\n";
    if (qi::phrase_parse(first, last, 
                *(
                     (&as_string [token_] [ _pass = ("var" == _1) ] >> swap_)
                   | omit[ token_ ]
                 ), space, to_swap))
    {
        std::cout << "Entries: " << to_swap.size() << "\n";

        // swap all swappables!
        for (auto& pair : to_swap)
        {
            std::cout << "Swap '" << pair.first << "' and '" << pair.second << "'\n";
            auto& a = pair.first;
            auto& b = pair.second;

            input.replace(a.begin(), b.end(), 
                    std::string(b.begin(), b.end()) +
                    std::string(a.end(), b.begin()) +
                    std::string(a.begin(), a.end()));
        }
    }
    std::cout << input << "\n";
    std::cout << "Remaining input: '" << std::string(first, last) << "'\n";
}
