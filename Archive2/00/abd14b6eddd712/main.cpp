#include <iostream>
#include <string>
#include <boost/regex.hpp>
 
int main()
{
    // Simple regular expression matching
    boost::regex expr("(.*)\\.(nef)", boost::regex_constants::ECMAScript |
                                      boost::regex_constants::icase);
    boost::cmatch m;
 
    for (auto const& fname : {"foo.nef", "bar.NeF", "baz.NEF"}) {
        if(boost::regex_match(fname, m, expr)) {
            std::cout << "matched: " << m[0] << '\n';
            std::cout << "         " << m[1] << '\n';
            std::cout << "         " << m[2] << '\n';
        }
    }
}
