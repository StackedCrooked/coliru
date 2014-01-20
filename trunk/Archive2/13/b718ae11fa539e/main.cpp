#include <iostream>
#include <cstdint>
#include <locale>
int main()
{
    std::uint32_t n = 0x98A8;

    std::wcout.sync_with_stdio(false);
    std::wcout.imbue(std::locale("en_US.utf8"));
    std::wcout << wchar_t(n) << '\n';
}