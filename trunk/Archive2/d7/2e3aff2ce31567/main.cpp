#include <iostream>
#include <exception>
#include <locale>
#include <clocale>
#include <boost/regex.hpp>

int main()
{
    std::setlocale(LC_ALL, "ja_JP.utf8");
    std::wstring str = L"\uff17"; // fullwidth digit seven, ７
    std::cout << "wctype returns: " << std::iswctype(str[0], std::wctype("jdigit")) << '\n';

    try {
        std::locale::global(std::locale("ja_JP.utf8"));
        std::cout << "regex_match returns: ";
        std::cout << boost::regex_match(str, boost::wregex(L"[[:jdigit:]]")) << '\n';
    } catch(const std::exception& e) {
            std::cout << e.what() << '\n';
    }
}
