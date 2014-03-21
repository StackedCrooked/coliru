#include <iostream>
#include <string>

std::string operator"" _s(const char* str, std::size_t) {
    return str;
}

int main() {
    auto x = "lol"_s;
    std::cout << x.size();
}