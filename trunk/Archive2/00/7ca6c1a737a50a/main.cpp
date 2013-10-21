#include <iostream>
#include <cwchar>
int main()
{
    const wchar_t* str = L"Hello, world!";
    std::wcout << "L\"" << str << "\" is " << std::wcslen(str) << '\n';
}