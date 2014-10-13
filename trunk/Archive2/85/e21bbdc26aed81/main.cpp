#include <iostream>
#include <clocale>
#include <string>
#include <iomanip> 
#include <sstream>
#include <locale>
#include <codecvt>
using namespace std;

std::string Narrow(const std::wstring& str) {
    std::ostringstream stm;
    const std::ctype<wchar_t> & ctfacet = std::use_facet< std::ctype<wchar_t>  >(stm.getloc());
    for (size_t i = 0; i < str.size(); ++i)
        stm << ctfacet.narrow(str[i], 0);
    return stm.str();
}

std::string ToUtf8(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
    return convert.to_bytes(wstr); 
}

int main()
{
    const wstring wstr = L"z\u00df\u6c34\U0001d10b"; // or L"zß水𝄋"
    
    cout << "wchar_t:";
    for(auto c : wstr) cout << '\n' << hex << (int32_t)c;
    
    cout << "\n\nNarrow:";
    for(auto c : Narrow(wstr)) cout << '\n' << hex << (int32_t)(uint8_t)c;

    cout << "\n\nToUtf8:";
    for(auto c : ToUtf8(wstr)) cout << '\n' << hex << (int32_t)(uint8_t)c;
}