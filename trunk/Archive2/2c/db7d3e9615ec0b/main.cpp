#include <iostream>
#include <string>
 
int main()
{
    const wchar_t* src = L" hello ";
    long l = (wcscmp(src, L"hello"));
    std::cout<<l;
}