#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <sstream>
 
int main()
{
    const std::u16string utf16 = u"Πυθαγόρας ὁ Σάμιος" ;
    const std::u16string another_utf16 = u"(Pythagoras of Samos)" ;
    
    // http://en.cppreference.com/w/cpp/locale/wstring_convert
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> codecvt ;
    
    std::ostringstream ograph ; 
    ograph << "the two UTF-16 strings contain: '" << codecvt.to_bytes(utf16) 
           << "' and '" << codecvt.to_bytes(another_utf16) << "'" ;
           
    std::cout << ograph.str() << '\n' ;
}