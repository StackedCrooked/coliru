#include <iostream>
#include <sstream>
#include <locale>
#include <codecvt>
int main()
{
    // wrap a UTF-8 string stream in a UCS4 wbuffer_convert
    std::stringbuf utf8buf(u8"z\u00df\u6c34\U0001d10b");  // or u8"zß水𝄋"
                       // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";
    std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv_in(&utf8buf);
    std::wistream ucsbuf(&conv_in);
    std::cout << "Reading from a UTF-8 stringbuf via wbuffer_convert:\n";
    for(wchar_t c; ucsbuf.get(c); )
        std::cout << std::hex << std::showbase << c << '\n';
 
    // wrap a UTF-8 aware std::cout in a UCS4 wbuffer_convert to output UCS4
    std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv_out(std::cout.rdbuf());
    std::wostream out(&conv_out);
    std::cout << "Sending UCS4 data to std::cout via wbuffer_convert:\n";
    out << L"z\u00df\u6c34\U0001d10b\n";
}
