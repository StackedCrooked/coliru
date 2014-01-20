#include <iostream>
#include <cstdint>
#include <locale>
#include <clocale>
int main()
{
    std::uint32_t n = 0x98A8;

    std::setlocale(LC_ALL, "en_US.utf8");
    std::wcout.imbue(std::locale("en_US.utf8"));
    std::wcout << wchar_t(n) << '\n';
}