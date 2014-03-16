#include <iostream>
#include <cwctype>
#include <clocale>
 
int main()
{
    wchar_t c = L'\u3000'; // Ideographic space ('　')
 
    std::cout << std::hex << std::showbase << std::boolalpha;
    std::cout << "in the default locale, iswblank(" << (std::wint_t)c << ") = "
              << (bool)std::iswblank(c) << '\n';
    std::setlocale(LC_ALL, "en_US.utf8");
    std::cout << "in Unicode locale, iswblank(" << (std::wint_t)c << ") = "
              << (bool)std::iswblank(c) << '\n';
}