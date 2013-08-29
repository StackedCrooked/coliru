#include <iostream>

#include <boost/algorithm/string.hpp>


void upper_print(std::string&& str) {
    boost::to_upper(str);
    // ^ (1) Should I use std::move here? (not specific to boost::to_upper())
    std::cout << str;
    // (2) Should I clear the string? (not specific to std::string)
}


int main() {
    std::string str = "Hello World!";
    upper_print(std::move(str));
}