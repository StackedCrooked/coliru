#include <string>
#include <codecvt>
#include <locale>
#include <iostream>

std::u16string to_utf16( std::string str ) // utf-8 to utf16
{ return std::wstring_convert< std::codecvt_utf8_utf16<char16_t>, char16_t >{}.from_bytes(str); }

std::string to_utf8( std::u16string str16 )
{ return std::wstring_convert< std::codecvt_utf8_utf16<char16_t>, char16_t >{}.to_bytes(str16); }

std::u32string to_utf32( std::string str )
{ return std::wstring_convert< std::codecvt_utf8<char32_t>, char32_t >{}.from_bytes(str); }

std::string to_utf8( std::u32string str32 )
{ return std::wstring_convert< std::codecvt_utf8<char32_t>, char32_t >{}.to_bytes(str32); }

std::wstring to_wchar_t( std::string str )
{ return std::wstring_convert< std::codecvt_utf8<wchar_t>, wchar_t >{}.from_bytes(str); }

std::string to_utf8( std::wstring wstr )
{ return std::wstring_convert< std::codecvt_utf8<wchar_t>, wchar_t >{}.to_bytes(wstr); }

int main()
{
    const std::string utf8 = "hello world!\n" ;

    const std::u16string utf16 = to_utf16( utf8 ) ;
    std::cout << to_utf8(utf16) ;

    const std::u32string utf32 = to_utf32( utf8 ) ;
    std::cout << to_utf8(utf32) ;
    
    const std::wstring wstr = to_wchar_t(utf8) ;
    std::wcout << wstr ;
    std::cout << to_utf8(wstr) << "---------------------\n" ;
}
