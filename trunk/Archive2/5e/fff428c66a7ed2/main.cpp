#include<iostream>
#include<string>

int main () {
    char x[] = { 'a', 'b', 'c',  0};
    
    std::wstring   ws   = reinterpret_cast<wchar_t*>(x);
    std::u16string u16s = reinterpret_cast<char16_t*>(x);
    
    std::wcout << L"sizeof(wchar_t):  "       << sizeof(wchar_t)
               << L"\twide string length: "   << ws.length()   
               << std::endl;

    std::wcout << L"sizeof(char16_t): "       << sizeof(char16_t)
               << L"\tu16string length:   "   << u16s.length()   
               << std::endl;
}