#include <iostream>
#include <fstream>
#include <string>
#include <locale>
 
struct codecvt_to_upper : std::codecvt<wchar_t, char, std::mbstate_t>
{
    explicit codecvt_to_upper(size_t r = 0)
        : std::codecvt<wchar_t, char, std::mbstate_t>(r) { }
 
    result do_in(state_type&,
              const extern_type* from,
              const extern_type* from_end,
              const extern_type*& from_next,
              intern_type* to,
              intern_type* to_end,
              intern_type*& to_next) const override
    {
        codecvt_to_upper::result res = codecvt_to_upper::error;
        const std::ctype<char>& ct = std::use_facet<std::ctype<char>>(std::locale());
 
        const extern_type* p = from;
        while (p != from_end && to != to_end) {
            *to++ = ct.toupper( *p++);
        }
 
        from_next = p;
        to_next = to;
        res = codecvt_to_upper::ok;
        return res;
    }
};
 
int main()
{
    std::locale ulocale( std::locale(), new codecvt_to_upper);
 
    std::wofstream("out.txt") << L"abc";
    std::wifstream in("out.txt");
    in.imbue(ulocale);
 
    wchar_t c;
 
    while (in >> c)
    {
        std::wcout << c;
    }
}