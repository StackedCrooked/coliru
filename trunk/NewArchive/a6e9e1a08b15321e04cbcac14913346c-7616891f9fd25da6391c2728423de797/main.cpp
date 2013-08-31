#include <vector>
#include <string>
#include <iostream>
#include <boost/spirit/include/karma.hpp>

namespace karma = boost::spirit::karma;

int main()
{
    const std::vector<std::vector<std::vector<std::string>>> v { { 
                { "a0", "a1", "a2" },
                { "a1", "a2", "a3" },
            }, {
                { "a2", "a3", "a4" },
                { "a3", "a4", "a5" },
            },
            {
                { "b0", "b1", "b2" },
                { "b1", "b2", "b3" },
            },
            {
                { "b2", "b3", "b4" },
                { "b3", "b4", "b5" },
     } };

    for (auto& d1 : v) {
        for (auto& d2 : d1) {
            for (auto& d3: d2)
                std::cout << d3 << " ";
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    using namespace boost::spirit::karma;
    std::cout << format_delimited(auto_, ' ', v) << "\n";
    std::cout << format(auto_ % ',' % ' ' % eol , v) << "\n";
    std::cout << format_delimited( ("{" << *auto_ << "}"), ' ', v) << "\n";
    std::cout << format_delimited( ("{\n" << ("\t{" << *auto_ << '}') % eol << "\n}\n") % eol, ' ', v) << "\n";
}
