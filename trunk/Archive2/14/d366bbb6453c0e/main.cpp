#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <iomanip>
#include <string>
#include <codecvt>
 
// utility wrapper to adapt locale-bound facets for wstring/wbuffer convert
template<class Facet>
struct deletable_facet : Facet
{
    template<class ...Args>
    deletable_facet(Args&& ...args) : Facet(std::forward<Args>(args)...) {}
    ~deletable_facet() {}
};
 
int main()
{
    // UTF-8 narrow multibyte encoding
    std::string data = u8"z\u00df\u6c34\U0001f34c";
                       // or u8"zß水🍌"
                       // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9f\x8d\x8c";
 
    std::ofstream("text.txt") << data;
 
    // using system-supplied locale's codecvt facet
    std::wifstream fin("text.txt");
    // reading from wifstream willl use codecvt<wchar_t, char, mbstate_t>
    // this locale's codecvt converts UTF-8 to UCS4 (on systems such as Linux)
    fin.imbue(std::locale("en_US.UTF-8"));
    std::cout << "The UTF-8 file contains the following UCS4 code points: \n";
    for (wchar_t c; fin >> c; )
        std::cout << "U+" << std::hex << std::setw(4) << std::setfill('0') << c << '\n';
 
    // using standard (locale-independent) codecvt facet
    std::wstring_convert<
        deletable_facet<std::codecvt<char16_t, char, std::mbstate_t>>, char16_t> conv16;
    std::u16string str16 = conv16.from_bytes(data);
 
    std::cout << "The UTF-8 file contains the following UTF-16 code points: \n";
    for (char16_t c : str16)
        std::cout << "U+" << std::hex << std::setw(4) << std::setfill('0') << c << '\n';
}