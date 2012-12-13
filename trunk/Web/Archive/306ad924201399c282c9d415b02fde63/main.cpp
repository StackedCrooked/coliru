#include <iostream>
#include <locale>

int main() {
    auto const& ctype = std::use_facet<std::ctype<char>>(std::locale("en_US.UTF-8"));
    std::string str = u8"Ä";
    std::cout << ctype.tolower(&str[0], &str[0] + str.size()) << '\n';
}