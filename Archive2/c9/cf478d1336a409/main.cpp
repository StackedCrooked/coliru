#include <iostream>
#include <string>
#include <boost/regex.hpp>

int main() {
    std::string orig("abc.bc");
    std::string::const_iterator start, end;
    start = orig.begin();
    end = orig.end();
    boost::match_results<std::string::const_iterator> what;
    boost::regex reg("[a-z]+", boost::regex::basic);
    bool found = regex_search(start, end,  what, reg, boost::match_posix);
    std::cout << found;
}