#include <type_traits>
#include <thread>
#include <iostream>
#include <sstream>

int main() {
    std::stringstream sstr;
    sstr.str("");
    sstr << " ";
    sstr << 10;
    std::cout << sstr.str();
}