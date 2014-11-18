#include <sstream>
#include <string>
#include <iostream>

int main() {
    std::stringstream ss("1000000000000000000    asdf");

    ss.exceptions(std::ios::failbit); // throws on all tested implementations
    
    try {
    int i;
    ss >> i; } catch(...) {std::cout << "exception\n"; }
    std::cout << ss.fail() << ' ' << ss.bad() << '\n';
}
