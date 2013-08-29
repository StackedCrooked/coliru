#include <iostream>
#include <locale>
#include <sstream>

struct my_facet : std::ctype<wchar_t>
{
    bool do_is(mask m, char_type c) const
    {
        if ((m & space) && c == L' ') {
            return false;
        }
        if ((m & space) && c == L',')
        {
            return true;
        }
        return ctype::do_is(m, c);
    }
};

int main()
{
    std::wstringstream ss(L"35.123445,-85.888762");
    ss.imbue(std::locale(ss.getloc(), new my_facet));
    
    double a, b;
    
    ss >> a >> b;
    
    std::wcout << "a = " << a << '\n'
               << "b = " << b << '\n';
}