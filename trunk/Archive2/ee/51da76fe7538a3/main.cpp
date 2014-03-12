#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
 
int main()
{
    
    const std::u16string utf16 = u"Πυθαγόρας ὁ Σάμιος (Pythagoras of Samos)" ;
    
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> codecvt ;
    std::cout << codecvt.to_bytes(utf16) << '\n' ;
}