#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <iomanip>
 
int main()
{
    // UTF-8 narrow multibyte encoding
    std::ofstream("text.txt") << u8"z\u00df\u6c34\U0001d10b"; // or u8"zß水𝄋"
                                           // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";
    std::wifstream fin("text.txt");
    fin.imbue(std::locale("en_US.UTF-8")); // this locale's codecvt<wchar_t, char, mbstate_t>
                                           // converts UTF-8 to UCS4
    std::cout << "The UTF-8 file contains the following wide characters: \n";
    for (wchar_t c; fin >> c; )
        std::cout << "U+" << std::hex << std::setw(4) << std::setfill('0') << c << '\n';
}