#include <iostream>
#include <string>
#include <codecvt>

int main()
{
    const wchar_t szBuffer[] = L"Convert this" ;
    const std::wstring wstr = L"and convert this too" ;

    // http://en.cppreference.com/w/cpp/locale/codecvt
    struct codecvt_w2c : public std::codecvt < wchar_t, char, std::mbstate_t > 
    { public: ~codecvt_w2c() {} }; // public destructor

    // http://en.cppreference.com/w/cpp/locale/wstring_convert
    std::wstring_convert<codecvt_w2c> converter( "*** conversion error ***" ) ;

    const std::string str = converter.to_bytes(szBuffer);
    std::cout << str << '\n' ;

    const std::string str2 = converter.to_bytes(wstr);
    std::cout << str2 << '\n' ;
}
