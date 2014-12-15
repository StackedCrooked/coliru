#include <iostream>
#include <fstream>
#include <string>
#include <locale>
 
int main()
{
    // GB18030 narrow multibyte encoding
    std::ofstream("text.txt") << "\x7a"              // letter 'z', U+007a
                                 "\x81\x30\x89\x38"  // letter 'ß', U+00df
                                 "\xcb\xae"          // CJK ideogram '水' (water), U+6c34
                                 "\x94\x32\xbc\x35"; // musical sign '𝄋' (segno), U+1d10b
    std::wifstream fin("text.txt");
    fin.imbue(std::locale(fin.getloc(),
              new std::codecvt_byname<wchar_t, char, std::mbstate_t>("zh_CN.gb18030")));
    for (wchar_t c; fin.get(c); )
        std::cout << std::hex << std::showbase << c << '\n';
}