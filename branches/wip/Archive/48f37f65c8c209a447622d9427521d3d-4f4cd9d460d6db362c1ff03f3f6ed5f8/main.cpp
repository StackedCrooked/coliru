#include <boost/regex.hpp>
#include <iostream>

int main() {
    boost::regex r("a+");
    boost::smatch m;
    boost::regex_search(std::string("xxxaaaxxx"), m, r);
    std::cout << std::string(m[0].first, m[0].second);
}
