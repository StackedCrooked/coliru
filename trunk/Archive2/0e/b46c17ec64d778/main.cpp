#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <iomanip>
 
// utility function for output
void hex_print(const std::string& s)
{
    std::cout << std::hex << std::setfill('0');
    for(unsigned char c : s)
        std::cout << std::setw(2) << static_cast<int>(c) << ' ';
    std::cout << std::dec << '\n';
}
 
int main()
{
    // wide character data
    std::wstring wstr =  L"z\u00df\u6c34\U0001d10b"; // or L"zß水𝄋"
 
    // wide to UTF-8
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv1;
    std::string u8str = conv1.to_bytes(wstr);
    std::cout << "UTF-8 conversion produced " << u8str.size() << " bytes:\n";
    hex_print(u8str);
 
    // wide to UTF-16le
    std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>> conv2;
    std::string u16str = conv2.to_bytes(wstr);
    std::cout << "UTF-16le conversion produced " << u16str.size() << " bytes:\n";
    hex_print(u16str);
}