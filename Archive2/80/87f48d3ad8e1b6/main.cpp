#include <string>
#include <iostream>


int foo(const std::string& s) {std::cout << s; return 0;}

std::string operator "" _s(const char *str, std::size_t len) {return std::string(str,len); std::cout << "ctor for str";}

int main() {
    foo("bar"_s);
    foo("baz"_s);
}