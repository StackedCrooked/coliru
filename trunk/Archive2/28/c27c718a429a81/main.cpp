#include <sstream>
#include <string>
#include <iostream>

int main() {
    //std::stringstream ss("");
    //std::stringstream ss("asdf");
    std::stringstream ss("1000000000000000000");

    ss.exceptions(std::ios::failbit); // throws on all tested implementations
    
    try {
    int i;
    ss >> i; } catch(...) {std::cout << "exception\n"; }
    std::cout << ss.fail() << ' ' << ss.bad() << '\n';
}
