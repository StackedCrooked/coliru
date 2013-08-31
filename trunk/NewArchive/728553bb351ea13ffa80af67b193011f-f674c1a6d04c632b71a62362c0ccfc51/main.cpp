#include <iostream>
#include <clocale>
#include <cstdlib>
#include <string>
int main()
{
    std::setlocale(LC_ALL, "en_US.utf8");
    std::string s = "03A0";
    wchar_t wstr = std::strtoul(s.c_str(), nullptr, 16);
    std::wcout << wstr;
}