#include <iostream>

#include <boost/algorithm/string.hpp>


void upper_print(std::string str) {
    boost::to_upper(str);
    std::cout << str;
}

int main() {
    std::string str = "Hello World!";
    upper_print(std::move(str));
}