#include <iostream>
#include <string>

int main() {
    int const i { 'a' };
    std::cout << std::showbase << std::hex << i << ' ' << std::dec << i << std::endl;
    wchar_t const c { 0x61 };
    std::wcout << c << std::endl;

    std::string const s { "é" };
    int const j { s.front() };
    unsigned char const k = s.back();
    std::cout << j << ' ' << int(k) << std::endl;
}