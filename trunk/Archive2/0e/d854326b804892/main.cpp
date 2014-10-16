#include <iostream>

wchar_t t = u'ي';
wchar_t tt = L'ي';
wchar_t ttt = U'ي';

int main()
{
    std::wcout << t << std::endl;
    std::wcout << tt << std::endl;
    std::wcout << ttt << std::endl;
}

