#include <iostream>
#include <string>

int main() {
    std::string s{'a', 'b', '\0', 'c'};
    std::cout << s.size() << '\n' << s << '\n' << s.c_str();
}