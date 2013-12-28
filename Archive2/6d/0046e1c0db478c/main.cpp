#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
 
int main()
{
    std::ofstream("text.txt") << u8"z\u6c34\U0001d10b";
 
    std::wifstream file1("text.txt");
    file1.imbue(std::locale("en_US.UTF8"));
    std::cout << "Normal read from file (using default UTF-8/UTF-32 codecvt)\n";
    for (wchar_t c; file1 >> c; )
        std::cout << std::hex << std::showbase << c << '\n';
 
    std::wifstream file2("text.txt");
    file2.imbue(std::locale(file2.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
    std::cout << "UTF-16 read from the same file (using codecvt_utf8_utf16)\n";
    for (wchar_t c; file2 >> c; )
        std::cout << std::hex << std::showbase << c << '\n';
}