#include <boost/spirit/include/karma.hpp>
#include <iostream>

int main() {
    using namespace boost::spirit::karma;

    symbols<int, std::string> reg;
    reg.add(1,"aaa")(2,"bbb")(3,"ccc")(4,"ddd");

    std::vector<int> v{1,2,1,4,3,1};
    std::cout << format(reg % ", ", v);
}
