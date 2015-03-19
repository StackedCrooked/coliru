// http://coliru.stacked-crooked.com/a/f24f90c0790d0e58
#include "boilerplate.hpp"

#include <iostream>

int main()
{
    std::wcout << basic_string<wchar_t, 'a', 'b', '[', 'i', ',', 'j', ']'> << L'\n';
}