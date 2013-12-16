#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
 
int main()
{
    // UTF-8 data. The character U+1d10b, musical sign segno, does not fit in UCS2
    std::string utf8 = u8"z\u6c34\U0001d10b";
 
    // the UTF-8 / UTF-16 standard conversion facet
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf16conv;
    std::u16string utf16 = utf16conv.from_bytes(utf8);
    std::cout << "UTF16 conversion produced " << utf16.size() << " code points:\n";
    for (char16_t c : utf16)
        std::cout << std::hex << std::showbase << c << '\n';
 
    // the UTF-8 / UCS2 standard conversion facet
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> ucs2conv;
    try {
        std::u16string ucs2 = ucs2conv.from_bytes(utf8);
    } catch(const std::range_error& e) {
        std::u16string ucs2 = ucs2conv.from_bytes(utf8.substr(0, ucs2conv.converted()));
        std::cout << "UCS2 failed after producing " << std::dec << ucs2.size()<<" characters:\n";
        for (char16_t c : ucs2)
            std::cout << std::hex << std::showbase << c << '\n';
    }
}