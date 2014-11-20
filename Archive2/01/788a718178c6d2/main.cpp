#include <string>

struct my_alloc : std::allocator<char> {};

int main() {
    std::string a = "Hallo!";
    std::basic_string<char, std::char_traits<char>, my_alloc> b = "Hallo!";
    a == b;
};