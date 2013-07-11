#include <iostream>
#include <string>

#include <boost/algorithm/string/compare.hpp>


int main() {
    std::cout << boost::algorithm::is_iless()(std::string("Hello"), std::string("hello")) << std::endl;     // :(
}