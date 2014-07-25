#include<iostream>
#include<string>

int main () {
    char x[] = { 'a', 'b', 'c', 0, 0, 0, 0, 0};
    
    std::wstring   ws   = reinterpret_cast<wchar_t*>(x);
    std::u16string u16s = reinterpret_cast<char16_t*>(x);
    
    std::cout << "sizeof(wchar_t):  "       << sizeof(wchar_t)
              << "\twide string length: "   << ws.length()   
              << std::endl;

    std::cout << "sizeof(char16_t): "       << sizeof(char16_t)
               << "\tu16string length:   "   << u16s.length()   
               << std::endl;
}