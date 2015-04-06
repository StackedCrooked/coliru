#include <iostream>
#include <locale>
#include <clocale>
#include <cwchar>
 
int main()
{
    char narrow_str[] = "z\u00df\u6c34\U0001f34c";
                    // or "zß水🍌"
                    // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9f\x8d\x8c";
    wchar_t warr[29]; // the expected string is 28 characters plus 1 null terminator
    std::setlocale(LC_ALL, "en_US.utf8");
 
    std::swprintf(warr, sizeof warr/sizeof *warr,
                  L"Converted from UTF-8: '%s'", narrow_str);
 
    std::wcout.imbue(std::locale("en_US.utf8"));
    std::wcout << warr << '\n';
}