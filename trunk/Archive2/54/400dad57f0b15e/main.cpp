#include <iostream>
#include <clocale>
#include <cstdlib>
int main()
{
    std::setlocale(LC_ALL, "en_US.utf8");
    const char* mbstr = u8"z\u00df\u6c34\U0001d10b"; // or u8"zß水𝄋"
                        // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";
    wchar_t wstr[5];
    std::mbstowcs(wstr, mbstr, 5);
    std::wcout << "wide string: " << wstr << '\n';
}