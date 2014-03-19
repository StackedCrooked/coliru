#include <iostream>
#include <string>
#include <locale>
#include <cstring>
 
int main()
{
    const char* u8_string = u8"双喜雙喜!";
 
    std::locale::global(std::locale("en_US.utf8"));
    auto& f = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(std::locale());
    std::mbstate_t mb = std::mbstate_t(); // initial shift state
    std::wstring wstr(100, ' '); 
    const char* from_next;
    wchar_t* to_next;
    f.in(mb, u8_string, u8_string + std::strlen(u8_string), from_next,
             &wstr[0], &wstr[wstr.size()], to_next);
    wstr.resize(to_next - &wstr[0]);
 
    const wchar_t* LB_str = wstr.c_str();
    std::wcout << LB_str << '\n';
}