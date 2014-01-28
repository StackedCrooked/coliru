#include <iostream>
#include <string>
#include <boost/regex.hpp>
 
int main()
{
    // Simple regular expression matching
    boost::regex expr("(.*)\\.(nef)", boost::regex_constants::ECMAScript |
                                      boost::regex_constants::icase);
 
    for (auto const& fname : {"foo.nef", "bar.NeF", "baz.NEF"}) {
        std::cout << fname << ": " << boost::regex_match(fname, expr) << '\n';
    }
}
