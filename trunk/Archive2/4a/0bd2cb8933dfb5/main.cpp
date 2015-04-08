#include <iostream>
#include <locale>
 
int main()
{
    std::wcout << "User-preferred locale setting is " << std::locale("").name().c_str() << '\n';
    // on startup, the global locale is the "C" locale
    std::wcout << 3000.01 << '\n';
    // replace the C++ global locale as well as the C locale with the user-preferred locale
    std::locale::global(std::locale(""));
    // use the new global locale for future wide character output
    std::wcout.imbue(std::locale());
    // output the same number again
    std::wcout << 500.01 << '\n';
    std::wcout << "sdfasdf爱舒" << std::endl;
}