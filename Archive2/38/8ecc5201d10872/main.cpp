#include <string>
#include <boost/utility.hpp>
#include <iostream>

const std::string int_t = "int";
const std::string float_t = "float";
const std::string string_t = "string";

template <typename T> const std::string& get_t();
template<> const std::string& get_t<int>() { return int_t; }
template<> const std::string& get_t<float>() { return float_t; }



int main() {
    std::cout << get_t<int>();


}
