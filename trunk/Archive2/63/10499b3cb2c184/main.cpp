#include<iostream>
#include<string>

int main () {
    char x[] = { 'a', 'b', 'c',  0};
    std::wstring   ws = reinterpret_cast<wchar_t*>(x);
    std::u16string u16s = reinterpret_cast<char16_t*>(x);
    
    std::wcout << ws.length()   << L" " << ws << std::endl;
    std::wcout << u16s.length() 
#if 0    
               << u16s /*<< there's std char16_t cout*/ 
#endif 
               << std::endl;
}