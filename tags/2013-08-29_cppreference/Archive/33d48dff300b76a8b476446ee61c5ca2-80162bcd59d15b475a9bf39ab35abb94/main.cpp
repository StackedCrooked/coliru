#include <wctype.h>
#include <iostream>

int main() {
    wchar_t str[2] = {::toupper(L'ß'), L'\0'};
    
    std::wcout << str;
}