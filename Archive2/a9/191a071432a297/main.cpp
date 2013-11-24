#include <iostream>
#include <codecvt>
 
int main()
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    char16_t const * s = u"Blah Blah Blah";
    std::cout << converter.to_bytes(s) << std::endl;;
}