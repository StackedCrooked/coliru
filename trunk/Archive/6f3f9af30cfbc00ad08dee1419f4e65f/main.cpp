#include <iostream>
#include <locale>

int main() {
    auto const& ctype = std::use_facet<std::ctype<char>>(std::locale(""));
    std::string str = u8"A";
    ctype.tolower(&str[0], &str[0] + str.size());
    std::cout << "" << '\n';
}